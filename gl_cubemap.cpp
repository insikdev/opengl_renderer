#include "pch.h"
#include "gl_cubemap.h"
#include "image.h"

Cubemap::Cubemap(const std::vector<std::string>& files)
{
    glGenTextures(1, &m_id);
    Bind();

    for (unsigned int i = 0; i < files.size(); i++) {
        Image image { files[i], false };

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image.GetWidth(), image.GetHeight(), 0, image.GetFormat(), GL_UNSIGNED_BYTE, image.GetData());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Cubemap::~Cubemap()
{
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

void Cubemap::Bind(void)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

void Cubemap::Unbind(void)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
