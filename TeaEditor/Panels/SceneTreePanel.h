#pragma once

#include "TeaEngine/Core/Base.h"
#include "TeaEngine/Scene/Scene.h"
#include "TeaEngine/Scene/Entity.h"
#include "Panel.h"
#include "entt/entity/fwd.hpp"

namespace Tea {

    class SceneTreePanel : public Panel
    {
    public:
        SceneTreePanel() = default;
        SceneTreePanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender() override;

        Entity GetSelectedEntity() const { return m_SelectionContext; };
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

}