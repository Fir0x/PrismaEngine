#pragma once

#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight(const Vector3f& direction, const Vector3f& color, const Material& material);

		void draw(const Matrix4f& viewMatrix) const;

	private:
		Vector3f m_direction;
		Vector3f m_color;
		const Material& m_material;
	};
}