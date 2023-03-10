#pragma once
#include "Ganymede/Core/Timestep.h"
#include "Ganymede/Core/Core.h"
#include "Ganymede/Core/Window.h"

#include "Ganymede/Core/LayerStack.h"
#include "Ganymede/Events/Event.h"
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/ImGui/ImGuiLayer.h"

namespace Ganymede {
    class GANYMEDE_API Application {
    public:
        Application();   
        virtual ~Application() = default;

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Ganymede::Application *CreateApplication();

}
