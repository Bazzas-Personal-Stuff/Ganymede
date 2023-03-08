#include "gnmpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ganymede {
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return Ref<Texture2D>(new OpenGLTexture2D(width, height));
        }

        GNM_CORE_ASSERT(false, "Invalid Renderer API")
        return nullptr;
    }

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

    Ref<Texture2D> Texture2D::Create(const glm::vec4& color) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return Ref<Texture2D>(new OpenGLTexture2D(color));
        }

        GNM_CORE_ASSERT(false, "Invalid Renderer API")
        return nullptr;
    }

}
