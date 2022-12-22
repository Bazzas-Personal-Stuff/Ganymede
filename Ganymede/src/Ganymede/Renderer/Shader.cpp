#include "gnmpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ganymede {
    Ref<Shader> Shader::Create(const std::string& filepath) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return Ref<Shader>(new OpenGLShader(filepath));
        }

        GNM_CORE_ASSERT(false, "Unknown RendererAPI")
        return nullptr;
        
    }

    Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return Ref<Shader>(new OpenGLShader(vertexSrc, fragmentSrc));
        }

        GNM_CORE_ASSERT(false, "Unknown RendererAPI")
        return nullptr;
    }
}
