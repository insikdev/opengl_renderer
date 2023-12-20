#version 460 core

in vec2 texCoord;

uniform sampler2D ourTexture;

out vec4 fragColor;

void main() {
	fragColor = texture(ourTexture, texCoord);
}