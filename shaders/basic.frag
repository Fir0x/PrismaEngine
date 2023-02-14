#version 450

#include "defines/structs.glsl"
#include "defines/constants.glsl"

layout(binding = 0) uniform Data {
	FrameContext frame;
};

layout(binding = 1) buffer Lights {
	PointLight pointLights[];
};

out vec4 output_color;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUV;

float attenuation(float distance, float linear, float quadratic)
{
	return 1.0 / (1.0 + linear * distance + quadratic * distance * distance);
}

vec3 lightContribution(PointLight light)
{
	vec3 normal = normalize(fragNormal);
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
	vec3 normal = normalize(fragNormal);
	vec3 acc = max(dot(frame.sunDirection, normal), 0.0) * frame.sunColor;

	for (unsigned int i = 0; i < frame.lightCount; i++)
		acc += lightContribution(pointLights[i]);

	vec3 color = DEFAULT_COLOR * acc;

	output_color = vec4(color, 1.0);
#endif
}