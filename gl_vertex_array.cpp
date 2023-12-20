#include "pch.h"
#include "gl_vertex_array.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
    Bind();
}

VertexArray::~VertexArray()
{
    if (m_id) {
        glDeleteVertexArrays(1, &m_id);
    }
}

void VertexArray::Bind(void)
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind(void)
{
    glBindVertexArray(0);
}

void VertexArray::SetAttribute(GLuint index, GLint count, GLenum type, GLboolean normalized, GLsizei stride, size_t offset)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, count, type, normalized, stride, (const void*)offset);
}
