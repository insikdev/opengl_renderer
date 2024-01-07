#version 460 core

in VS_OUT
{
    vec2 TexCoords;
} frag_in;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main() {
	FragColor = texture(ourTexture, frag_in.TexCoords);
}