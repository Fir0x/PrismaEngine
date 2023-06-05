#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "Transform.h"
#include "core/maths/public/Matrix3.h"
#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "rendering/public/MeshRenderer.h"

namespace PrismaEngine
{
	class SceneObject
	{
	public:
		SceneObject(const MeshRenderer& renderer);
		SceneObject(const Vector3f& pos, const MeshRenderer& renderer);

		Transform& transform();
		void draw() const;

	private:
		Transform m_transform;
		MeshRenderer m_renderer;

		Matrix3f processNormalMatrix(const Matrix4f& model, const Matrix4f& view) const;
	};
}