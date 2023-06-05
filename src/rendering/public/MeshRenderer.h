#pragma once

#include "Material.h"
#include "core/maths/public/Matrix4.h"
#include "geometry/public/StaticMesh.h"

namespace PrismaEngine
{
	class MeshRenderer
	{
	public:
		MeshRenderer(std::shared_ptr<const StaticMesh> mesh, const Material& matreial);

		void draw(const Matrix4f& model) const;

	private:
		std::shared_ptr<const StaticMesh> m_mesh;
		Material m_material;
	};
}