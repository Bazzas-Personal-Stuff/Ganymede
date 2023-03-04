﻿#include "gnmpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Ganymede {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GNM_CORE_ASSERT(data, "Failed to load image at \"{0}\"", path);
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
        

        stbi_image_free(data);        
    }

    OpenGLTexture2D::OpenGLTexture2D(const glm::vec4 &color) {
        m_Path = "";
        m_Width = 1;
        m_Height = 1;


        glm::vec4 scaledColor = glm::clamp(color, 0.0f, 1.0f) * 255.0f;
        stbi_uc data[4] = {(stbi_uc) scaledColor.r, (stbi_uc) scaledColor.g, (stbi_uc) scaledColor.b, (stbi_uc) scaledColor.a };
        
        int channels = 4;
        int internalFormat = GL_RGBA8;
        int dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
        glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_RendererID);
    }
}
