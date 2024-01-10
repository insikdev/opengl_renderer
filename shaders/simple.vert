#version 460 core

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;

uniform mat4 world;
uniform float id;

out VS_OUT
{
	vec3 PosWorld;
	vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    float id;
} vs_out;

void main() {
    mat4 invTransWorld = transpose(inverse(world));

    vs_out.PosWorld = vec3(world * vec4(aPos, 1.0));
    vs_out.Normal = mat3(invTransWorld) * aNormal;
    vs_out.TexCoords = aTexCoord;
    vs_out.Tangent = mat3(invTransWorld) * aTangent;
    vs_out.id = id;

    gl_Position = projection * view * world * vec4(aPos, 1.0);
}