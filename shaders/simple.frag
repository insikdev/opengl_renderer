#version 460 core

struct Light {
	vec3 pos;
	vec3 dir;
	float cutoffStart;
	float cutoffEnd;
};

layout (std140, binding = 1) uniform Lights
{
	Light light;
};

in VS_OUT
{
	vec3 PosWorld;
	vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
	float id;
} frag_in;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	float shininess;
};

uniform Material material;
uniform vec3 cameraPos;
uniform int select;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 FragColor2;

vec3 CalcDirLight(Light light, vec3 N, vec3 V) {
	vec3 L = normalize(-light.dir);
	float diff = max(dot(N, L), 0.0);

	vec3 R = reflect(-L, N);
	float spec = pow(max(dot(V, R), 0.0), material.shininess);

	vec3 diffuseColor = texture(material.diffuse, frag_in.TexCoords).rgb;
	vec3 specularColor = texture(material.specular, frag_in.TexCoords).rgb;

	return diffuseColor * diff + specularColor * spec;
}

vec3 CalcSpotLight(Light light, vec3 L, vec3 N, vec3 V) {
	return vec3(0.0);
}


void main() {
	vec3 texNorm = normalize(texture(material.normal, frag_in.TexCoords).xyz * 2.0 - 1.0);
	vec3 N = normalize(frag_in.Normal);
	vec3 T = normalize(frag_in.Tangent);
	vec3 B = cross(N, T);
	mat3 TBN = mat3(T, B, N);
		
	vec3 pixelNorm = normalize(TBN * texNorm);
	vec3 V = normalize(cameraPos - frag_in.PosWorld);

	if (select == 1) {
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		vec3 result = vec3(0.0);

		// result += CalcDirLight(light, pixelNorm, V);

		vec3 L = normalize(light.pos - frag_in.PosWorld);

		float theta = dot(L, normalize(-light.dir));
		float intensity = clamp((theta - light.cutoffEnd) / (light.cutoffStart- light.cutoffEnd), 0.0, 1.0);
		
		if (intensity > 0.0) {
			vec3 diffuseColor = texture(material.diffuse, frag_in.TexCoords).rgb;
			vec3 specularColor = texture(material.specular, frag_in.TexCoords).rgb;

			vec3 N = normalize(frag_in.Normal);
			float diff = max(dot(N, L), 0.0);
			vec3 diffuse = diff * diffuseColor;

			vec3 reflectDir = reflect(-L, N);
			float spec = pow(max(dot(V, reflectDir), 0.0), material.shininess);
			vec3 specular = spec * specularColor;

			result += (diffuse + specular) * intensity;
		}

		FragColor = vec4(result, 0.0);
	}

	FragColor2 = vec4(frag_in.id,0.0f,0.0f,0.0f);
}