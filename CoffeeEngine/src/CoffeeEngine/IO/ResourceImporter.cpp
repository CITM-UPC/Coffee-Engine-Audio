#include "ResourceImporter.h"

namespace Coffee {
    std::filesystem::path ResourceImporter::m_cachePath = ".CoffeeEngine/Cache/Resources";

    Ref<Texture> ResourceImporter::ImportTexture(const std::filesystem::path& path, bool srgb, bool cache)
    {
        if (!cache)
        {
            return CreateRef<Texture>(path, srgb);
        }

        std::filesystem::create_directories(m_cachePath);

        std::filesystem::path cachedFilePath = m_cachePath / (path.filename().stem() += ".res");

        if (std::filesystem::exists(cachedFilePath))
        {
            const Ref<Resource>& resource = LoadFromCache(cachedFilePath, ResourceFormat::Binary);
            return std::static_pointer_cast<Texture>(resource);
        }
        else
        {
            Ref<Texture> texture = CreateRef<Texture>(path, srgb);
            ResourceSaver::SaveToCache(texture);
            return texture;
        }
    }

    Ref<Resource> ResourceImporter::LoadFromCache(const std::filesystem::path& path, ResourceFormat format)
        {
            switch (format)
            {
                case ResourceFormat::Binary:
                    return BinaryDeserialization(path);
                    break;
                case ResourceFormat::JSON:
                    return JSONDeserialization(path);
                    break;
            }
        }

    Ref<Resource> ResourceImporter::BinaryDeserialization(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::binary);
        cereal::BinaryInputArchive archive(file);
        Ref<Resource> resource;
        archive(resource);
        return resource;
    }

    Ref<Resource> ResourceImporter::JSONDeserialization(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        cereal::JSONInputArchive archive(file);
        Ref<Resource> resource;
        archive(resource);
        return resource;
    }
}