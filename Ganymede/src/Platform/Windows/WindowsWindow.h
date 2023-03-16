#pragma once
#include "Ganymede/Core/Window.h"
#include "Ganymede/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Ganymede {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;
        inline unsigned int GetWidth() const override {return m_Data.Width;}
        inline unsigned int GetHeight() const override {return m_Data.Height;}

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn &callback) override {m_Data.EventCallback = callback;}
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
        
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
        virtual void* GetNativeWindow() const override { return m_Window; }
        
        GLFWwindow* m_Window;
        Ref<GraphicsContext> m_Context;
        
        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        
        WindowData m_Data;
    };
}
