#version 450

#include "../defines/structs.glsl"
#include "../defines/constants.glsl"

layout(binding = 0) uniform Data {
	FrameContext frame;
};

layout(binding = 1) buffer Lights {
	PointLight pointLights[];
};

layout(binding = 0) uniform sampler2D albedoTexture;
layout(binding = 1) uniform sampler2D normalTexture;

out vec4 output_color;

in vec3 fragPos;
in vec2 fragUV;

float attenuation(float distance, float linear, float quadratic)
{
	return 1.0 / (1.0 + linear * distance + quadratic * distance * distance);
}

vec3 lightContribution(PointLight light, vec3 normal)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float lightDistance = length(light.position - fragPos);

	vec3 diffuse = max(dot(lightDir, normal), 0.0) * light.color;
	diffuse *= attenuation(lightDistance, light.linear, light.quadratic);

	vec3 viewDir = normalize(-fragPos);
	vec3 reflectedDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0), 32);
	float specularStrength = 0.5;
	vec3 specular = specularStrength * spec * light.color;

	return diffuse + specular;
}

void main()
{
#ifdef SHOW_UV
	output_color = vec4(fragUV, 0.0, 1.0);
#elif defined(SHOW_NORMAL)
	output_color = vec4(fragNormal, 1.0);
#else
#ifdef ALBEDO_TEX
	vec3 albedo = texture2D(albedoTexture, fragUV).rgb;
#else
	vec3 albedo = DEFAULT_COLOR;
#endif
#ifdef NORMAL_MAPPED
	vec3 normalMap = texture2D(normalTexture, fragUV).xyz;
	normalMap = normalMap * 2.0 - 1.0;
	vec3 tangent = normalize(fragTangent);
	vec3 bitangent = normalize(fragBitangent);
	vec3 normal = normalMap.x * tangent + normalMap.y * bitangent + normalMap.z * fragNormal;
#else
	vec3 normal = normalize(fragNormal);
#endif
	vec3 acc = max(dot(frame.sunDirection, normal), 0.0) * frame.sunColor;

	for (unsigned int i = 0; i < frame.lightCount; i++)
		acc += lightContribution(pointLights[i], normal);

	vec3 color = albedo * acc;

	output_color = vec4(abs(color), 1.0);
#endif
}