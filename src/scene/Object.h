#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "components/Transform.h"
#include "components/MeshRenderer.h"

namespace BerylEngine
{
	class Object
	{
	private:
		Transform m_transform;
		MeshRenderer m_renderer;

		glm::mat3 processNormalMatrix(const glm::mat4& model, const glm::mat4& view) const;

	public:
		Object(const MeshRenderer& renderer);
		Object(const glm::vec3& pos, const MeshRenderer& renderer);

		Transform& transform();
		void draw() const;
	};
}