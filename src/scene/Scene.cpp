#include "Scene.h"

#include "../core/TypedBuffer.h"
#include "shaderDefs.h"

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

	size_t Scene::addLight(const PointLight& light)
	{
		m_lights.push_back(light);
		return m_lights.size() - 1;
	}

	void Scene::removeLight(size_t index)
	{
		m_lights.erase(m_lights.begin() + index);
	}

	void Scene::render(const Camera& camera) const
	{
		ShaderDefs::FrameContext context;
		context.camera.viewMatrix = camera.viewMatrix();
		context.camera.projectionMatrix = camera.projectionMatrix();
		context.sunDirection = glm::normalize(glm::mat3(camera.viewMatrix()) * glm::normalize(glm::vec3(0.8f, 0.1f, 0.3f)));
		context.sunColor = glm::vec3(0.6f, 0.6f, 0.6f);
		context.lightCount = glm::uint(m_lights.size());

		TypedBuffer<ShaderDefs::FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		std::vector<ShaderDefs::PointLight> mappedLights;
		for (const auto& light : m_lights)
		{
			ShaderDefs::PointLight mappedLight;
			mappedLight.position = camera.viewMatrix() * glm::vec4(light.position(), 1.0f);
			mappedLight.radius = light.radius();
			mappedLight.color = light.color();
			light.coefficients(mappedLight.linear, mappedLight.quadratic);
			mappedLights.push_back(mappedLight);
		}
		TypedBuffer<ShaderDefs::PointLight> lightBuffer(mappedLights.data(), mappedLights.size());
		lightBuffer.bind<BufferUsageType::ShaderStorage>(1);

		for (const auto& obj : m_objects)
			obj.draw();
	}
}