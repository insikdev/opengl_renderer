#include "pch.h"
#include "gl_uniform.h"

Uniform::Uniform(GLuint index, GLenum usage, GLsizeiptr stride, GLsizeiptr count)
    : Buffer { GL_UNIFORM_BUFFER, usage, nullptr, stride, count }
    , m_index { index }
{
    glBindBufferRange(m_type, m_index, m_id, 0, stride * count);
}

void Uniform::CopyData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glBufferSubData(m_type, offset, size, data);
}
