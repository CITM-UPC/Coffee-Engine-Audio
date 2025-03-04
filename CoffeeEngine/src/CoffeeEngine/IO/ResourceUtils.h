﻿#pragma once

#include <filesystem>
#include "CoffeeEngine/IO/Resource.h"

namespace Coffee {

    inline ResourceType GetResourceTypeFromExtension(const std::filesystem::path& path)
    {
        auto extension = path.extension();

        if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
        {
            return ResourceType::Texture2D;
        }
        else if(extension == ".hdr")
        {
            return ResourceType::Cubemap;
        }
        else if(extension == ".glb" || extension == ".gltf" || extension == ".fbx" || extension == ".obj")
        {
            return ResourceType::Model;
        }
        else if(extension == ".glsl")
        {
            return ResourceType::Shader;
        }

        return ResourceType::Unknown;
    }

    inline std::string ResourceTypeToString(ResourceType type)
    {
        switch (type)
        {
        case ResourceType::Texture2D:
            return "Textur2D";
        case ResourceType::Cubemap:
            return "Cubemap";
        case ResourceType::Model:
            return "Model";
        case ResourceType::Mesh:
            return "Mesh";
        case ResourceType::Shader:
            return "Shader";
        case ResourceType::Material:
            return "Material";
        default:
            return "Unknown";
        }
    }

}