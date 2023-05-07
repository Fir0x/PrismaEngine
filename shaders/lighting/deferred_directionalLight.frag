#version 450

#include "../defines/structs.glsl"
#include "../defines/constants.glsl"

layout(binding = 0) uniform Data {
	FrameContext frame;
};

layout(binding = 0) uniform sampler2D albedoTexture;
layout(binding = 1) uniform sampler2D normalTexture;

out vec4 output_color;

in vec3 fragPos;
in vec2 fragUV;

uniform vec3 lightDirection;
uniform vec3 lightColor;

vec3 remapNormal(vec3 normal)
{
	return normal * 2.0 - vec3(1.0);
}

void main()
{
	ivec2 fragCoord = ivec2(gl_FragCoord.xy);
	vec3 albedo = texelFetch(albedoTexture, fragCoord, 0).xyz;
	vec3 normal = remapNormal(texelFetch(normalTexture, fragCoord, 0).xyz);

	vec3 acc = max(dot(lightDirection, normal), 0.0) * lightColor;
	vec3 color = albedo * acc;

	output_color = vec4(color, 1.0);
}