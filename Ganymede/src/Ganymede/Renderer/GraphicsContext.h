#pragma once

struct GLFWwindow;
namespace Ganymede {
    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void Bind() = 0;
        virtual void SwapBuffers() = 0;

        static Ref<GraphicsContext> Create(GLFWwindow* windowHandle);
    };
}
