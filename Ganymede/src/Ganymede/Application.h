#pragma once
#include "Ganymede/Core.h"
#include "Ganymede/Window.h"

#include "Ganymede/LayerStack.h"
#include "Ganymede/Events/Event.h"
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/ImGui/ImGuiLayer.h"
#include "Ganymede/Renderer/Shader.h"
#include "Renderer/Buffer.h"

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

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
