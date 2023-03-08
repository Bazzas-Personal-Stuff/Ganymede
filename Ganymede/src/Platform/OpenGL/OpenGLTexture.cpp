#include "gnmpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Ganymede {

    // Create blank texture with no data
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height) {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    // Create texture from specified image asset path
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GNM_CORE_ASSERT(data, "Failed to load image at \"{0}\"", path);
        m_Width = width;
        m_Height = height;

        if(channels == 4) {
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        }
        else if(channels == 3) {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
        

        stbi_image_free(data);        
    }

    // Create 1x1 color texture
    OpenGLTexture2D::OpenGLTexture2D(const glm::vec4 &color) {
        m_Path = "";
        m_Width = 1;
        m_Height = 1;
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;


        glm::vec4 scaledColor = glm::clamp(color, 0.0f, 1.0f) * 255.0f;
        stbi_uc data[4] = {(stbi_uc) scaledColor.r, (stbi_uc) scaledColor.g, (stbi_uc) scaledColor.b, (stbi_uc) scaledColor.a };

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size) {
        uint32_t bytesPerPixel;
        switch(m_DataFormat) {
        case GL_RGBA:
            bytesPerPixel = 4;
            break;
        case GL_RGB:
            bytesPerPixel = 3;
            break;
        default:
            bytesPerPixel = 3;
        }

        GNM_CORE_ASSERT(size == m_Width * m_Height * bytesPerPixel, "Texture data of size {0} is not equal to its dimensions {1} x {2}", size, m_Width, m_Height);
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_RendererID);
    }
}
