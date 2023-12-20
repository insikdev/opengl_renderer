#pragma once

#include "gl_object.h"

class VertexArray : public GLBindableObject {
public:
    VertexArray();
    ~VertexArray();

public:
    void Bind(void) override;
    void Unbind(void) override;
    void SetAttribute(GLuint index, GLint count, GLenum type, GLboolean normalized, GLsizei stride, size_t offset);
};
