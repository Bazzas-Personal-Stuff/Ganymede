﻿#pragma once
#include "Ganymede/Core.h"
#include "Ganymede/Layer.h"

namespace Ganymede {
    class GANYMEDE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.f;
        
    };
}
