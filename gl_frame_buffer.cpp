#include "pch.h"
#include "gl_frame_buffer.h"
#include "gl_texture.h"
#include "gl_render_buffer.h"

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
    : m_width { width }
    , m_height { height }
{
    glGenFramebuffers(1, &m_id);
    Initialize();
}

FrameBuffer::~FrameBuffer()
{
    if (m_id) {
        glDeleteFramebuffers(1, &m_id);
    }
}

void FrameBuffer::Bind(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FrameBuffer::Unbind(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;

    p_color.reset();
    p_depthStencil.reset();

    Initialize();
}

void FrameBuffer::DrawToScreen(void)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void FrameBuffer::Initialize(void)
{
    Bind();

    p_color = std::make_unique<Texture>(m_width, m_height, GL_RGBA);
    p_color->SetFilter(GL_LINEAR, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, p_color->GetId(), 0);

    p_depthStencil = std::make_unique<RenderBuffer>(m_width, m_height, GL_DEPTH24_STENCIL8);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, p_depthStencil->GetId());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        SPDLOG_ERROR("Failed to create frame buffer");
        exit(EXIT_FAILURE);
    }

    Unbind();
}
