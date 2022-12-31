#pragma once
#include "Ganymede/Core/Core.h"
#include "Ganymede/Core/Layer.h"

namespace Ganymede {
    class GANYMEDE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer() override = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.f;
        
    };
}
