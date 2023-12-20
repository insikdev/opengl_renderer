#include "pch.h"
#include "gl_buffer.h"

Buffer::Buffer(GLenum type, GLenum usage, const void* pData, GLsizeiptr stride, GLsizeiptr count)
    : m_type { type }
    , m_usage { usage }
    , m_stride { stride }
    , m_count { count }
{
    glGenBuffers(1, &m_id);
    glBindBuffer(m_type, m_id);
    glBufferData(m_type, m_stride * m_count, pData, m_usage);
}

Buffer::~Buffer()
{
    if (m_id) {
        glDeleteBuffers(1, &m_id);
    }
}

void Buffer::Bind(void)
{
    // glBindBuffer(m_type, m_id);
}

void Buffer::Unbind(void)
{
    // glBindBuffer(m_type, 0);
}
