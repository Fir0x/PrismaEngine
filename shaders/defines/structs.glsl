struct CameraData
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

struct FrameContext
{
	CameraData camera;
	vec3 sunDirection;
	uint lightCount;
	vec3 sunColor;
	float pad2;
};

struct PointLight
{
	vec3 position;
	float radius;
	vec3 color;
	float linear;
	float quadratic;
};