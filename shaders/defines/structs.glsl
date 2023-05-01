struct CameraData
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

struct ViewportData
{
	uint width;
	uint height;
};

struct FrameContext
{
	CameraData camera;
	ViewportData viewport;
};

struct PointLight
{
	vec3 position;
	float radius;
	vec3 color;
	float linear;
	float quadratic;
};