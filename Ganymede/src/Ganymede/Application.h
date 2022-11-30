#pragma once
#include "Ganymede/Core.h"
#include "Ganymede/Window.h"

#include "Ganymede/LayerStack.h"
#include "Ganymede/Events/Event.h"
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/ImGui/ImGuiLayer.h"

namespace Ganymede {
    class GANYMEDE_API Application {
    public:
        Application();   
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
