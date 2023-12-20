#pragma once

#include "gl_object.h"

class Shader;

struct ShaderInfo {
    const std::string& filename;
    const GLenum type;
};

class Program : public GLObject {
public:
    Program(const std::vector<ShaderInfo>& shaders);
    ~Program();

public:
    void Use(void);
    void SetUniform(const std::string& name, const glm::mat4& value);

private:
    void LinkShaders(const std::vector<ShaderInfo>& shaders);
};
