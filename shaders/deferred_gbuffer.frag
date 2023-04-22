#version 450

#include "defines/structs.glsl"
#include "defines/constants.glsl"

layout(binding = 0) uniform Data {
	FrameContext frame;
};

layout(binding = 0) uniform sampler2D albedoTexture;
layout(binding = 1) uniform sampler2D normalTexture;

out vec4 output_color;
out vec3 output_normals;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUV;
in vec3 fragTangent;
in vec3 fragBitangent;

void main()
{
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

	output_color = vec4(albedo, 1.0);
	output_normals = normal;
}