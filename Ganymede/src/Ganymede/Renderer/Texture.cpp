#include "gnmpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ganymede {
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return Ref<Texture2D>(new OpenGLTexture2D(path));
        }

        GNM_CORE_ASSERT(false, "Invalid Renderer API")
        return nullptr;
    }
}
