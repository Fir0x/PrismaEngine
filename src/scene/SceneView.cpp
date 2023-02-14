#include "SceneView.h"

namespace BerylEngine
{
	SceneView::SceneView(const Scene& scene)
		: m_scene(scene)
	{
	}

	SceneView::SceneView(const Scene& scene, const glm::vec3& cameraPosition)
		: m_scene(scene), m_camera(cameraPosition)
	{
	}

	SceneView::SceneView(const Scene& scene, const glm::mat4& frustum, const glm::vec3& cameraPosition)
		: m_scene(scene), m_camera(frustum, cameraPosition)
	{
	}

	Camera& SceneView::camera()
	{
		return m_camera;
	}

	void SceneView::render() const
	{
		m_scene.render(m_camera);
	}
}