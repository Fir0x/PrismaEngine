#pragma once

#include "Camera.h"
#include "Scene.h"

#include "core/maths/public/Vector2.h"
#include "core/maths/public/Vector3.h"

namespace PrismaEngine
{
	class SceneView
	{
	public:
		SceneView(const Scene& scene);
		SceneView(const Scene& scene, const Vector3f& cameraPosition);
		SceneView(const Scene& scene, const Vector3f& cameraPosition, float aspectRatio);

		Camera& camera();

		void renderGeometry(const Vector2i& windowSizes) const;
		void renderLights(const Vector2i& windowSizes) const;
		void renderWireframes(const Vector2i& windowSizes) const;

	private:
		const Scene& m_scene;
		Camera m_camera;
	};
}

