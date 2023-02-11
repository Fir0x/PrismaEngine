#version 450

#include "defines.glsl"

out vec4 output_color;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUV;

void main()
{
#ifdef SHOW_UV
	output_color = vec4(fragUV, 0.0, 1.0);
#else
	output_color = vec4(DEFAULT_COLOR, 1.0);
#endif
}