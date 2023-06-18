struct CameraData
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

struct ViewportData
{
	int width;
	int height;
	int pad0;
	int pad1;
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