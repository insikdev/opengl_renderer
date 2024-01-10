#pragma once

// library
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

// std
#include <string>
#include <vector>
#include <memory>
#include <cassert>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
};

struct MeshInfo {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct Light {
    alignas(16) glm::vec3 pos;
    alignas(16) glm::vec3 dir;
    alignas(4) float cutoffStart;
    alignas(4) float cutoffEnd;
};

struct GuiOptions {
    bool wireframe { false };
    bool cullBackface { false };
    bool drawNormal { false };
    Light* light;
};