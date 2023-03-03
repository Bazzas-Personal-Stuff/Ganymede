#include "gnmpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ganymede {
    Ref<VertexArray> VertexArray::Create() {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        }

        GNM_CORE_ASSERT(false, "Invalid Renderer API")
        return nullptr;
    }

}
