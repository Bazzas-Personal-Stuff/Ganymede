#pragma once
#include "imgui.h"
#include "Ganymede/Core.h"
#include "Ganymede/Layer.h"
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/Events/KeyEvent.h"
#include "Ganymede/Events/MouseEvent.h"

namespace Ganymede {
    class GANYMEDE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;
        void OnEvent(Event &event) override;
        void OnAttach() override;
        void OnDetach() override;

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        void UpdateKeyModifiers(int mods);
        ImGuiKey GLFWToImGuiKey(int key);

        float m_Time = 0.f;
        
    };
}
