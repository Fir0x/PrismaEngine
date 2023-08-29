#version 450

in vec3 barycentricCoords;

out vec4 output_color;

uniform vec3 color;

void main() {
	float minBarycentricCoord = min(min(barycentricCoords.x, barycentricCoords.y), barycentricCoords.z);
	float intensity = max(sign(0.01 - minBarycentricCoord), 0.0);;
	output_color = vec4(color * intensity, 1.0);
}