﻿#include "gnmpch.h"
#include "WindowsWindow.h"

namespace Ganymede {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        WindowsWindow::Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        WindowsWindow::Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        GNM_CORE_INFO("Creating window {0} - ({1}, {2})", props.Title, props.Width, props.Height);

        if(!s_GLFWInitialized) {
            int success = glfwInit();
            GNM_CORE_ASSERT(success, "Could not initialize GLFW");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if(enabled) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
        
        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return m_Data.VSync;
    }


}
