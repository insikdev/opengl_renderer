#version 460 core

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
};


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 world;
uniform float id;

out VS_OUT
{
    vec2 TexCoords;
    float id;
} vs_out;

void main() {
    gl_Position = projection * view * world * vec4(aPos, 1.0);
    vs_out.TexCoords = aTexCoord;
    vs_out.id = id;
}