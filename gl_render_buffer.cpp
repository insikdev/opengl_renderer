#include "pch.h"
#include "gl_render_buffer.h"

RenderBuffer::RenderBuffer(uint32_t width, uint32_t height, GLenum format)
    : m_width { width }
    , m_height { height }
    , m_format { format }
{
    glGenRenderbuffers(1, &m_id);
    Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, format, m_width, m_height);
}

RenderBuffer::~RenderBuffer()
{
    if (m_id) {
        glDeleteRenderbuffers(1, &m_id);
    }
}

void RenderBuffer::Bind(void)
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

void RenderBuffer::Unbind(void)
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
