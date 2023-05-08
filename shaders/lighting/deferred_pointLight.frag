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
layout(binding = 2) uniform sampler2D depthTexture;

uniform uint lightIndex;

out vec4 outputColor;

float attenuation(float distance, float linear, float quadratic)
{
	return 1.0 / (1.0 + linear * distance + quadratic * distance * distance);
}

vec3 lightContribution(PointLight light, vec3 position, vec3 normal)
{
	vec3 lightDir = normalize(light.position - position);
	float lightDistance = length(light.position - position);

	vec3 diffuse = max(dot(lightDir, normal), 0.0) * light.color;
	//diffuse *= attenuation(lightDistance, light.linear, light.quadratic);

	vec3 viewDir = normalize(-position);
	vec3 reflectedDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0), 32);
	float specularStrength = 0.5;
	vec3 specular = specularStrength * spec * light.color;

	return diffuse + specular;
}

vec3 remapNormal(vec3 normal) {
    return normalize(normal * 2.0 - vec3(1.0));
}

vec3 unproject(vec2 uv, float depth, mat4 inv_viewproj) {
    const vec3 ndc = vec3(uv * 2.0 - vec2(1.0), depth);
    const vec4 p = inv_viewproj * vec4(ndc, 1.0);
    return p.xyz / p.w;
}

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    vec3 color = texelFetch(albedoTexture, coord, 0).xyz;
    
    vec3 normal = remapNormal(texelFetch(normalTexture, coord, 0).xyz);
    vec2 uv = coord / vec2(frame.viewport.width, frame.viewport.height);
    float depth = texelFetch(depthTexture, coord, 0).x;

    vec3 position = unproject(uv, depth, inverse(frame.camera.projectionMatrix));
    PointLight light = pointLights[lightIndex];

    const vec3 acc = lightContribution(light, position, normal);

    outputColor = vec4(color * acc, 1.0);
}