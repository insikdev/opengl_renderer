#include "pch.h"
#include "gl_texture.h"
#include "image.h"

Texture::Texture(int width, int height, GLenum format)
    : m_width { width }
    , m_height { height }
    , m_format { format }
{
    glGenTextures(1, &m_id);
    Bind();
    // only allocate memory not copy data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, nullptr);
}

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &m_id);
    Bind();

    Image image { path };
    m_width = image.GetWidth();
    m_height = image.GetHeight();
    m_format = image.GetFormat();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, image.GetData());

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
