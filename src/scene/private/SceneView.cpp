#include "../public/SceneView.h"

namespace PrismaEngine
{
	SceneView::SceneView(const Scene& scene)
		: m_scene(scene)
	{
	}

	SceneView::SceneView(const Scene& scene, const Vector3f& cameraPosition)
		: m_scene(scene), m_camera(cameraPosition)
	{
	}

	SceneView::SceneView(const Scene& scene, const Vector3f& cameraPosition, float aspectRatio)
		: m_scene(scene), m_camera(cameraPosition, aspectRatio)
	{
	}

	Camera& SceneView::camera()
	{
		return m_camera;
	}

	void SceneView::renderGeometry(const Vector2i& windowSizes) const
	{
		m_scene.drawGeometry(m_camera, windowSizes);
	}

	void SceneView::renderLights(const Vector2i& windowSizes) const
	{
		m_scene.drawLights(m_camera, windowSizes);
	}

	void SceneView::renderWireframes(const Vector2i& windowSizes) const
	{
		m_scene.drawWireframes(m_camera, windowSizes);
	}
}