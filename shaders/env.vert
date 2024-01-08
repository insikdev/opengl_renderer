#version 460 core

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 position;

uniform mat4 world;

void main() {
    normal = mat3(transpose(inverse(world))) * aNormal;
    position = vec3(world * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(position, 1.0);
}