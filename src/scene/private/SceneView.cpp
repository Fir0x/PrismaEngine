#include "../public/SceneView.h"

namespace PrismaEngine
{
	SceneView::SceneView(const Scene& scene)
		: m_scene(scene)
	{
	}

	SceneView::SceneView(const Scene& scene, const glm::vec3& cameraPosition)
		: m_scene(scene), m_camera(cameraPosition)
	{
	}

	SceneView::SceneView(const Scene& scene, const glm::vec3& cameraPosition, float aspectRatio)
		: m_scene(scene), m_camera(cameraPosition, aspectRatio)
	{
	}

	Camera& SceneView::camera()
	{
		return m_camera;
	}

	void SceneView::renderGeometry(const glm::ivec2& windowSizes) const
	{
		m_scene.drawGeometry(m_camera, windowSizes);
	}

	void SceneView::renderLights(const glm::ivec2& windowSizes) const
	{
		m_scene.drawLights(m_camera, windowSizes);
	}
}