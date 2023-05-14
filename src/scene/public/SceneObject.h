#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "Transform.h"
#include "core/maths/public/vec3f.h"
#include "rendering/public/MeshRenderer.h"

namespace PrismaEngine
{
	class SceneObject
	{
	public:
		SceneObject(const MeshRenderer& renderer);
		SceneObject(const Vec3f& pos, const MeshRenderer& renderer);

		Transform& transform();
		void draw() const;

	private:
		Transform m_transform;
		MeshRenderer m_renderer;

		glm::mat3 processNormalMatrix(const glm::mat4& model, const glm::mat4& view) const;
	};
}