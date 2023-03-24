#include "gnmpch.h"
#include "GraphicsContext.h"

#include "RendererAPI.h"
#include "Platform/DX11/DX11Context.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ganymede {
    Ref<GraphicsContext> GraphicsContext::Create(GLFWwindow *windowHandle) {
        Ref<GraphicsContext> ctxRef = nullptr;

        switch(RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            ctxRef = CreateRef<OpenGLContext>(windowHandle);
            break;
        case RendererAPI::API::DX11:
            ctxRef = CreateRef<DX11Context>(windowHandle);
            break;

        default:
            GNM_CORE_ASSERT(false, "Unknown RendererAPI");
        }

        ctxRef->Bind();
        return ctxRef;
    }
}
