#include "gnmpch.h"
#include "WindowsWindow.h"

#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/Events/KeyEvent.h"
#include "Ganymede/Events/MouseEvent.h"
#include "Ganymede/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ganymede {
    static bool s_GLFWInitialized = false;
    static void GLFWErrorCallback(int error, const char* description) {
        GNM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Scope<Window> Window::Create(const WindowProps& props) {
        // TODO: Cross-platform
        return Scope<Window>(new WindowsWindow(props));
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        GNM_PROFILE_FUNCTION();
        WindowsWindow::Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        GNM_PROFILE_FUNCTION();
        WindowsWindow::Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props) {
        GNM_PROFILE_FUNCTION();
        
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        GNM_CORE_INFO("Creating window {0} - ({1}, {2})", props.Title, props.Width, props.Height);


        if(!s_GLFWInitialized) {
            GNM_PROFILE_SCOPE("glfwInit");
            
            int success = glfwInit();
            GNM_CORE_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        {
            GNM_PROFILE_SCOPE("glfwCreateWindow");
            m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        }

        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, mods, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key, mods);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, mods, 1);
                    data.EventCallback(event);
                    break;
                }
                default: {
                    GNM_CORE_ERROR("Key action out of bounds: {0}", action);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode, 0);
            data.EventCallback(event);            
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button, mods);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button, mods);
                    data.EventCallback(event);
                    break;
                }
                default: {
                    GNM_CORE_ERROR("Mouse Button action out of bounds: {0}", action);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }


    void WindowsWindow::Shutdown() {
        GNM_PROFILE_FUNCTION();
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate() {
        GNM_PROFILE_FUNCTION();
        GraphicsContext::Bind(m_Context);
        glfwPollEvents();
        RenderCommand::SwapBuffers();
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
