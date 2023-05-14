#pragma once

#include "Camera.h"
#include "Scene.h"

#include "core/maths/public/vec2i.h"
#include "core/maths/public/vec3f.h"

namespace PrismaEngine
{
	class SceneView
	{
	public:
		SceneView(const Scene& scene);
		SceneView(const Scene& scene, const Vec3f& cameraPosition);
		SceneView(const Scene& scene, const Vec3f& cameraPosition, float aspectRatio);

		Camera& camera();

		void renderGeometry(const Vec2i& windowSizes) const;
		void renderLights(const Vec2i& windowSizes) const;

	private:
		const Scene& m_scene;
		Camera m_camera;
	};
}

