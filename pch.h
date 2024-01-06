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
};

struct MeshInfo {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct GuiOptions {
    bool wireframe { false };
    bool cullBackface { false };
    bool drawNormal { false };
};