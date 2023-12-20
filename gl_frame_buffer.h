#pragma once

#include "gl_object.h"

class Texture;
class RenderBuffer;

class FrameBuffer : public GLBindableObject {
public:
    FrameBuffer(uint32_t width, uint32_t height);
    ~FrameBuffer();

public:
    void Bind(void) override;
    void Unbind(void) override;
    void Resize(uint32_t width, uint32_t height);
    void DrawToScreen(void);

private:
    void Initialize(void);

private:
    std::unique_ptr<Texture> p_color;
    std::unique_ptr<RenderBuffer> p_depthStencil;

private:
    uint32_t m_width;
    uint32_t m_height;
};
