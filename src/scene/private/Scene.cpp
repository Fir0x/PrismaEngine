#include "../public/Scene.h"

#include "RHI/public/TypedBuffer.h"
#include "rendering/public/shaderDefs.h"

namespace PrismaEngine
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

	size_t Scene::addLight(const DirectionalLight& light)
	{
		m_directionaLights.push_back(light);
		return m_directionaLights.size() - 1;
	}

	size_t Scene::addLight(const PointLight& light)
	{
		m_pointLights.push_back(light);
		return m_pointLights.size() - 1;
	}

	void Scene::drawGeometry(const Camera& camera, const glm::ivec2& windowSizes) const
	{
		ShaderDefs::FrameContext context;
		context.camera.viewMatrix = camera.viewMatrix();
		context.camera.projectionMatrix = camera.projectionMatrix();
		context.viewport.width = windowSizes.x;
		context.viewport.height = windowSizes.y;

		TypedBuffer<ShaderDefs::FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		for (const auto& obj : m_objects)
			obj.draw();
	}

	void Scene::drawLights(const Camera& camera, const glm::ivec2& windowSizes) const
	{
		ShaderDefs::FrameContext context;
		context.camera.viewMatrix = camera.viewMatrix();
		context.camera.projectionMatrix = camera.projectionMatrix();
		context.viewport.width = windowSizes.x;
		context.viewport.height = windowSizes.y;

		TypedBuffer<ShaderDefs::FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		for (const auto& light : m_directionaLights)
			light.draw(camera.viewMatrix());
		//std::vector<ShaderDefs::PointLight> mappedLights;
		//for (const auto& light : m_lights)
		//{
		//	ShaderDefs::PointLight mappedLight;
		//	mappedLight.position = camera.viewMatrix() * glm::vec4(light.position(), 1.0f);
		//	mappedLight.radius = light.radius();
		//	mappedLight.color = light.color();
		//	light.coefficients(mappedLight.linear, mappedLight.quadratic);
		//	mappedLights.push_back(mappedLight);
		//}
		//TypedBuffer<ShaderDefs::PointLight> lightBuffer(mappedLights.data(), mappedLights.size());
		//lightBuffer.bind<BufferUsageType::ShaderStorage>(1);
	}
}