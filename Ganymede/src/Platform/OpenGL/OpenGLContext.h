#pragma once
#include "Ganymede/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ganymede {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void Bind() override { s_CurrentContext = this; }
        virtual void SwapBuffers() override;
        
        static OpenGLContext* GetCurrent() { return s_CurrentContext; }

    private:
        GLFWwindow* m_WindowHandle;
        
        static OpenGLContext* s_CurrentContext;
    };
}
