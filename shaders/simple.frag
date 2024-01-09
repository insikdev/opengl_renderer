#version 460 core

in VS_OUT
{
    vec2 TexCoords;
	float id;
} frag_in;

uniform sampler2D ourTexture;
uniform int select;

//out vec4 FragColor;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 FragColor2;

void main() {
	if (select == 1) {
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		FragColor = texture(ourTexture, frag_in.TexCoords);
	}
	FragColor2 = vec4(frag_in.id,0.0f,0.0f,0.0f);
}