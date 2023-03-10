#include "gnmpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ganymede {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle) {
        GNM_CORE_ASSERT(windowHandle, "Window handle is null")
    }

    void OpenGLContext::Init() {
        GNM_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GNM_CORE_ASSERT(status, "Failed to initialize Glad")

        GNM_CORE_INFO("OpenGL Info:");
        GNM_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        GNM_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        GNM_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    #ifdef GNM_ENABLE_ASSERTS
        int versionMajor, versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        GNM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Ganymede requires at least OpenGL 4.5");
    #endif
    }

    void OpenGLContext::SwapBuffers() {
        GNM_PROFILE_FUNCTION();
        glfwSwapBuffers(m_WindowHandle);
    }

}
