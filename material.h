#pragma once

class Texture;
class Program;

class Material {
public:
    Material() = default;
    ~Material() = default;

public:
    void SetToProgram(const Program* program) const;

public:
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> specular;
    float shininess { 32.0f };
};
