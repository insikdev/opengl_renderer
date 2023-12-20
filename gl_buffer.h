#pragma once

#include "gl_object.h"

class Buffer : public GLBindableObject {
public:
    Buffer(GLenum type, GLenum usage, const void* pData, GLsizeiptr stride, GLsizeiptr count);
    ~Buffer();

public:
    void Bind(void) override;
    void Unbind(void) override;

public: // getter
    GLsizeiptr GetStride(void) const { return m_stride; }
    GLsizeiptr GetCount(void) const { return m_count; }

private:
    GLenum m_type;
    GLenum m_usage;
    GLsizeiptr m_stride;
    GLsizeiptr m_count;
};
