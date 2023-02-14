#version 450

#include "defines/structs.glsl"

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

layout(binding = 0) uniform Data {
	FrameContext frame;
};

uniform mat4 modelMatrix;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUV;

void main()
{
	fragPos = vec3(frame.camera.viewMatrix * modelMatrix * vec4(position, 1.0));
	mat3 normalMatrix = mat3(transpose(inverse(frame.camera.viewMatrix * modelMatrix)));
	fragNormal = normalMatrix * normal;
	fragUV = uv;

	gl_Position = frame.camera.projectionMatrix * vec4(fragPos, 1.0);
}