#include "SceneObject.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

namespace BerylEngine
{
	SceneObject::SceneObject(const MeshRenderer& renderer)
		: m_transform(), m_renderer(renderer)
	{
	}

	SceneObject::SceneObject(const glm::vec3& pos, const MeshRenderer& renderer)
		: m_transform(pos), m_renderer(renderer)
	{
	}

	glm::mat3 SceneObject::processNormalMatrix(const glm::mat4& model, const glm::mat4& view) const
	{
		return glm::mat3(glm::transpose(glm::inverse(view * model)));
	}

	Transform& SceneObject::transform()
	{
		return m_transform;
	}

	void SceneObject::draw() const
	{
		glm::mat4 model = m_transform.getMatrix();
		m_renderer.draw(model);
	}
}