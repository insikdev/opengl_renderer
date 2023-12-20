#pragma once

#include "gl_object.h"

class Shader : public GLObject {
public:
    Shader(const std::string& filename, GLenum type);
    ~Shader();
};
