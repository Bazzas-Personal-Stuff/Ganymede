#include "gnmpch.h"
#include "RendererAPI.h"

#include "Platform/DX11/DX11RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#define GNM_RENDERER_OPENGL 1
// #define GNM_RENDERER_DIRECTX11 1

namespace Ganymede {
#if GNM_RENDERER_OPENGL
    RendererAPI::API RendererAPI::s_API = API::OpenGL;
#elif GNM_RENDERER_DIRECTX11
    RendererAPI::API RendererAPI::s_API = API::DX11;
#else
    RendererAPI::API RendererAPI::s_API = API::None;
#endif

    Scope<RendererAPI> RendererAPI::Create() {
        switch(s_API) {

        case API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case API::OpenGL:
            return CreateScope<OpenGLRendererAPI>();
        case API::DX11:
            return CreateScope<DX11RendererAPI>();
        }
        
        GNM_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}
