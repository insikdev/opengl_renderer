#include "pch.h"
#include "gl_cubemap.h"
#include <stb_image.h>

Cubemap::Cubemap(const std::vector<std::string>& files)
{
    glGenTextures(1, &m_id);
    Bind();

    int width, height, channels;

    for (unsigned int i = 0; i < files.size(); i++) {
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(files[i].c_str(), &width, &height, &channels, 0);

        if (!data) {
            SPDLOG_ERROR("failed to load image: {}", files[i].c_str());
            exit(EXIT_FAILURE);
        }

        GLenum format = GL_RGBA;
        if (channels == 3) {
            format = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
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
