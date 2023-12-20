#pragma once

#include "gl_object.h"

class RenderBuffer : public GLBindableObject {
public:
    RenderBuffer(uint32_t width, uint32_t height, GLenum format);
    ~RenderBuffer();

public:
    void Bind(void) override;
    void Unbind(void) override;

private:
    uint32_t m_width {};
    uint32_t m_height {};
    GLenum m_format;
};
