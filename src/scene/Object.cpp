#include "Object.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

#include "../core/glErrors.h"

namespace BerylEngine
{
	Object::Object(const MeshRenderer& renderer)
		: m_transform(), m_renderer(renderer)
	{
	}

	Object::Object(const glm::vec3& pos, const MeshRenderer& renderer)
		: m_transform(pos), m_renderer(renderer)
	{
	}

	glm::mat3 Object::processNormalMatrix(const glm::mat4& model, const glm::mat4& view) const
	{
		return glm::mat3(glm::transpose(glm::inverse(view * model)));
	}

	Transform& Object::transform()
	{
		return m_transform;
	}

	void Object::draw() const
	{
		glm::mat4 model = m_transform.getMatrix();
		m_renderer.draw(model);
	}
}