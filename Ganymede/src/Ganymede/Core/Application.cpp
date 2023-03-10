#include "gnmpch.h"
#include "Application.h"

#include "Ganymede/Core/Time.h"
#include "Ganymede/Renderer/Renderer.h"

namespace Ganymede {

    Application* Application::s_Instance = nullptr;
    
    Application::Application() {
        GNM_PROFILE_FUNCTION();
        
        GNM_CORE_ASSERT(s_Instance == nullptr, "Application instance already exists")
        s_Instance = this;
        m_Window = Window::Create();
        m_Window->SetEventCallback(GNM_BIND_EVENT_FN(Application::OnEvent));
        // m_Window->SetVSync(false);
        Renderer::Init();
        
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

    }


    void Application::PushLayer(Layer *layer) {
        GNM_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }


    void Application::PushOverlay(Layer *overlay) {
        GNM_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }


    void Application::OnEvent(Event& e) {
        GNM_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GNM_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(GNM_BIND_EVENT_FN(Application::OnWindowResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if(e.Handled) {
                break;
            }
        }
    }


    void Application::Run() {
        while (m_Running) {
            GNM_PROFILE_SCOPE("Run Loop");
            Time::UpdateDelta();

            if(!m_Minimized) {
                {
                    GNM_PROFILE_SCOPE("LayerStack Update");
                    
                    for(Layer* layer : m_LayerStack) {
                        layer->OnUpdate();    
                    }
                }
            }
            
            m_ImGuiLayer->Begin();
            {
                GNM_PROFILE_SCOPE("LayerStack ImGuiRender");
                for(Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();
            
            m_Window->OnUpdate();
        }
    }


    bool Application::OnWindowClose(WindowCloseEvent &e) {
        GNM_PROFILE_FUNCTION();
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        GNM_PROFILE_FUNCTION();
        if(e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }


}
