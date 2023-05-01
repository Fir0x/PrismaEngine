#pragma once

#include "Camera.h"
#include "Scene.h"

namespace PrismaEngine
{
	class SceneView
	{
	public:
		SceneView(const Scene& scene);
		SceneView(const Scene& scene, const glm::vec3& cameraPosition);
		SceneView(const Scene& scene, const glm::vec3& cameraPosition, float aspectRatio);

		Camera& camera();

		void renderGeometry(const glm::ivec2& windowSizes) const;
		void renderLights(const glm::ivec2& windowSizes) const;

	private:
		const Scene& m_scene;
		Camera m_camera;
	};
}

