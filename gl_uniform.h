#pragma once

#include "gl_buffer.h"

class Uniform : public Buffer {
public:
    Uniform(GLuint index, GLenum usage, GLsizeiptr stride, GLsizeiptr count);
    ~Uniform() = default;

public:
    void CopyData(GLintptr offset, GLsizeiptr size, const void* data);

private:
    const GLuint m_index;
};
