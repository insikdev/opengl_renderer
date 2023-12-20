#include "pch.h"
#include "gl_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(int width, int height, GLenum format)
    : m_width { width }
    , m_height { height }
    , m_format { format }
{
    glGenTextures(1, &m_id);
    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, nullptr);
}

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &m_id);
    Bind();

    int channelCount;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* pData = stbi_load(path.c_str(), &m_width, &m_height, &channelCount, 0);

    if (!pData) {
        SPDLOG_ERROR("Failed to load image : {}", path);
        exit(EXIT_FAILURE);
    }

    if (channelCount == 3) {
        m_format = GL_RGB;
    } else if (channelCount == 4) {
        m_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, pData);
    stbi_image_free(pData);

    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

void Texture::Bind(void)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind(void)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFilter(GLint minFilter, GLint magFilter)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(GLint sWrap, GLint tWrap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}
