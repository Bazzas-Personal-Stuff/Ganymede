#include "gnmpch.h"
#include "Application.h"
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/Log.h"

namespace Ganymede {
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() {
    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();
        }
    }
}