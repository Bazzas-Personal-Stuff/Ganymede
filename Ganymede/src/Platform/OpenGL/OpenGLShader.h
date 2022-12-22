﻿#pragma once
#include "Ganymede/Renderer/Shader.h"

// TODO: Remove
typedef unsigned int GLenum;

namespace Ganymede {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader() override;
        virtual const std::string& GetName() const override { return m_Name; }

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& shaderSource);
        GLenum ShaderTypeFromString(const std::string& typeString);

        virtual void Bind() const override;
        virtual void Unbind() const override;
        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& value);
        void UploadUniformMat4(const std::string& name, const glm::mat4& value);
    private:
        void Compile(const std::unordered_map<GLenum, std::string>& source);
    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };
    
}
