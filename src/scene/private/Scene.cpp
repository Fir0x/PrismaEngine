#include "../public/Scene.h"

#include "core/maths/public/Vector4.h"
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

	void Scene::drawGeometry(const Camera& camera, const Vector2i& windowSizes) const
	{
		ShaderDefs::FrameContext context;
		context.camera.viewMatrix = camera.viewMatrix();
		context.camera.projectionMatrix = camera.projectionMatrix().transpose();
		context.viewport.width = windowSizes.x;
		context.viewport.height = windowSizes.y;

		TypedBuffer<ShaderDefs::FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		for (const auto& obj : m_objects)
			obj.draw();
	}

	void Scene::drawLights(const Camera& camera, const Vector2i& windowSizes) const
	{
		ShaderDefs::FrameContext context;
		size_t test = sizeof(ShaderDefs::FrameContext);
		context.camera.viewMatrix = camera.viewMatrix();
		context.camera.projectionMatrix = camera.projectionMatrix().transpose();
		context.viewport.width = windowSizes.x;
		context.viewport.height = windowSizes.y;

		TypedBuffer<ShaderDefs::FrameContext> contextBuffer(&context, 1);
		contextBuffer.bind<BufferUsageType::UniformBuffer>(0);

		const Matrix4f transposedView = camera.viewMatrix().transpose();

		for (const auto& light : m_directionaLights)
			light.draw(context.camera.viewMatrix);

		std::vector<ShaderDefs::PointLight> mappedLights;
		for (const auto& light : m_pointLights)
		{
			ShaderDefs::PointLight mappedLight;
			mappedLight.position = Transform::transformPoint(context.camera.viewMatrix, light.position());
			mappedLight.radius = light.radius();
			mappedLight.color = light.color();
			light.coefficients(mappedLight.linear, mappedLight.quadratic);
			mappedLights.push_back(mappedLight);
		}
		TypedBuffer<ShaderDefs::PointLight> lightBuffer(mappedLights.data(), mappedLights.size());
		lightBuffer.bind<BufferUsageType::ShaderStorage>(1);

		for (unsigned int i = 0; i < m_pointLights.size(); i++)
			m_pointLights[i].draw(i);
	}
}