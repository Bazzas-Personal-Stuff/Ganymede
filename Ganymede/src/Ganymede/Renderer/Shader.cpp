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
            return CreateRef<OpenGLShader>(filepath);
        }

        GNM_CORE_ASSERT(false, "Unknown RendererAPI")
        return nullptr;
        
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch(Renderer::GetAPI()) {
        case RendererAPI::API::None:
            GNM_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        GNM_CORE_ASSERT(false, "Unknown RendererAPI")
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
        GNM_CORE_ASSERT(!Exists(name), "Shader with name '{}' already exists", name);
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader) {
        Add(shader->GetName(), shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name) {
        GNM_CORE_ASSERT(Exists(name), "Shader with name '{0}' does not exist", name);
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
