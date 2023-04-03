#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "Transform.h"
#include "rendering/public/MeshRenderer.h"

namespace BerylEngine
{
	class SceneObject
	{
	public:
		SceneObject(const MeshRenderer& renderer);
		SceneObject(const glm::vec3& pos, const MeshRenderer& renderer);

		Transform& transform();
		void draw() const;

	private:
		Transform m_transform;
		MeshRenderer m_renderer;

		glm::mat3 processNormalMatrix(const glm::mat4& model, const glm::mat4& view) const;
	};
}