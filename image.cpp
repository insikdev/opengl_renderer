#include "pch.h"
#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const std::string& filename, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);

    if (!m_data) {
        SPDLOG_ERROR("Failed to load image : {}", filename);
        exit(EXIT_FAILURE);
    }
}

Image::~Image()
{
    stbi_image_free(m_data);
}
