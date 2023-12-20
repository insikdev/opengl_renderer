#pragma once

#include "gl_object.h"

class Texture : public GLBindableObject {
public:
    Texture(int width, int height, GLenum format);
    Texture(const std::string& path);
    ~Texture();

public:
    void Bind(void) override;
    void Unbind(void) override;
    void SetFilter(GLint minFilter, GLint magFilter);
    void SetWrap(GLint sWrap, GLint tWrap);

private:
    int m_width {};
    int m_height {};
    GLenum m_format;
};
