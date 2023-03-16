#pragma once

struct GLFWwindow;
namespace Ganymede {
    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static void Bind(const Ref<GraphicsContext>& context) { s_CurrentContext = context; }
        static Ref<GraphicsContext> GetCurrent() { return s_CurrentContext; }
        static Ref<GraphicsContext> Create(GLFWwindow* windowHandle);

    private:
        static Ref<GraphicsContext> s_CurrentContext;
    };
}
