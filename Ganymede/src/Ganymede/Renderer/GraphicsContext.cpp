#include "gnmpch.h"
#include "GraphicsContext.h"

#include "RendererAPI.h"
#include "Platform/DX11/DX11Context.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ganymede {
    Ref<GraphicsContext> GraphicsContext::s_CurrentContext = nullptr;

    Ref<GraphicsContext> GraphicsContext::Create(GLFWwindow *windowHandle) {
        switch(RendererAPI::GetAPI()) {

        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLContext>(windowHandle);
        case RendererAPI::API::DX11:
            return CreateRef<DX11Context>(windowHandle);
        }

        GNM_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}
