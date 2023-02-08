#version 450

out vec4 output_color;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUV;

void main()
{
	output_color = vec4(fragUV, 0.0, 1.0);
}