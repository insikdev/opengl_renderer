#version 460 core

//out vec4 FragColor;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 FragColor2;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
    FragColor2 = vec4(0.0,0.0,0.0,0.0);
}