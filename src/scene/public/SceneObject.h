#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "Transform.h"
#include "core/maths/public/mat3f.h"
#include "core/maths/public/mat4f.h"
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

		Mat3f processNormalMatrix(const Mat4f& model, const Mat4f& view) const;
	};
}