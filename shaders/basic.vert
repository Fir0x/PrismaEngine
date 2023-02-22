#version 450

#include "defines/structs.glsl"

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;
layout(location=3) in vec4 tangentData;

layout(binding = 0) uniform Data {
	FrameContext frame;
};

uniform mat4 modelMatrix;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUV;
out vec3 fragTangent;
out vec3 fragBitangent;

void main()
{
	fragPos = vec3(frame.camera.viewMatrix * modelMatrix * vec4(position, 1.0));
	mat3 normalMatrix = mat3(transpose(inverse(frame.camera.viewMatrix * modelMatrix)));
	fragNormal = normalMatrix * normal;
	fragUV = uv;
	fragTangent = mat3(frame.camera.viewMatrix * modelMatrix) * tangentData.xyz;
	fragBitangent = cross(fragTangent, fragNormal) * (tangentData.w > 0.0 ? 1.0 : -1.0);

	gl_Position = frame.camera.projectionMatrix * vec4(fragPos, 1.0);
}