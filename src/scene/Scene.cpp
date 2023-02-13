#include "Scene.h"

#include "../core/TypedBuffer.h"

namespace BerylEngine
{
	size_t Scene::addObject(const SceneObject& object)
	{
		m_objects.push_back(object);
		return m_objects.size() - 1;
	}

	void Scene::removeObject(size_t index)
	{
		m_objects.erase(m_objects.begin() + index);
	}

	void Scene::render(Camera& camera)
	{
		struct FrameContext
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};

		FrameContext context = { camera.getViewMatrix(), camera.getProjectionMatrix() };
		TypedBuffer<FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		for (const auto& obj : m_objects)
			obj.draw();
	}
}