#include "gnmpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/DX11/DX11VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ganymede {
    Ref<VertexArray> VertexArray::Create() {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        case RendererAPI::API::DX11:
            return CreateRef<DX11VertexArray>();
        }

        GNM_CORE_ASSERT(false, "Invalid Renderer API")
        return nullptr;
    }

}
