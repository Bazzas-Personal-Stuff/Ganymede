#include "gnmpch.h"
#include "OpenGLShader.h"
#include <fstream>
#include <ranges>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Ganymede {
    OpenGLShader::OpenGLShader(const std::string& filepath) {
        std::string fileSource = ReadFile(filepath);
        auto shaderSources = PreProcess(fileSource);
        Compile(shaderSources);

        // Extract name from filepath
        size_t fileNamePos = filepath.find_last_of("/\\");
        fileNamePos = fileNamePos == std::string::npos ? 0 : fileNamePos + 1;
        size_t fileExtPos = filepath.rfind('.');
        size_t fileNameSize = fileExtPos == std::string::npos ? filepath.size() - fileNamePos : fileExtPos - fileNamePos;
        m_Name = filepath.substr(fileNamePos, fileNameSize);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name) {
        std::unordered_map<GLenum, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(shaderSources);        
    }


    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath) {
        std::string result;
        std::ifstream inFile(filepath, std::ios::in | std::ios::binary);
        if(inFile) {
            inFile.seekg(0, std::ios::end);
            result.resize(inFile.tellg());
            inFile.seekg(0, std::ios::beg);
            inFile.read(&result[0], result.size());
            inFile.close();
        }
        else {
            GNM_CORE_ERROR("Could not open shader file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& shaderSource) {
        std::unordered_map<GLenum, std::string> splitSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = shaderSource.find(typeToken);
        while(pos != std::string::npos) {
            // Parse type name, e.g. "#type [typename]"
            size_t eol = shaderSource.find_first_of("\r\n", pos);
            GNM_CORE_ASSERT(eol != std::string::npos, "Shader syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string shaderType = shaderSource.substr(begin, eol - begin);
            GNM_CORE_ASSERT(shaderType == "vertex" || shaderType == "fragment" || shaderType == "pixel", "Invalid shader type '{0}'", shaderType);

            // Get source code until next #type or eof
            size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
            pos = shaderSource.find(typeToken, nextLinePos);
            splitSources[ShaderTypeFromString(shaderType)] = shaderSource.substr(nextLinePos, pos - (
                nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
        }
        
        return splitSources;
    }

    GLenum OpenGLShader::ShaderTypeFromString(const std::string& typeString) {
        if(typeString == "vertex") {
            return GL_VERTEX_SHADER;
        }
        if(typeString == "fragment" || typeString == "pixel") {
            return GL_FRAGMENT_SHADER;
        }
        
        GNM_CORE_ASSERT(false, "Invalid shader type '{0}'", typeString);
        return 0; 
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

        GLuint program = glCreateProgram();
        GNM_CORE_ASSERT(shaderSources.size() <= 2, "Maximum of 2 shaders per file exceeded, attempted to compile {0} shaders.", shaderSources.size())
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        for (auto& kv : shaderSources) {
            GLenum shaderType = kv.first;
            const std::string& shaderSource = kv.second;

            // Create an empty shader handle
            GLuint shader = glCreateShader(shaderType);
            
            // Send the shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar* sourceCStr = shaderSource.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);

            // Compile the shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

                // We don't need the shader anymore.
                glDeleteShader(shader);

                // Use the infoLog as you see fit.
                GNM_CORE_ASSERT(false, "Shader compilation failure:\n{0}", infoLog.data())

                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex] = shader;
            glShaderIDIndex++;
        }


        glLinkProgram(program);
        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for(auto id : glShaderIDs) {
                glDeleteShader(id);
            }

            // Use the infoLog as you see fit.
            GNM_CORE_ASSERT(false, "Shader link failure:\n{0}", infoLog.data())

            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        for(auto id : glShaderIDs) {
            glDetachShader(program, id);
        }
        
        m_RendererID = program;
    }


    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
    
    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

}
