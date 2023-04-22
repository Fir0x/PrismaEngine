#pragma once

#include "Material.h"
#include "geometry/public/StaticMesh.h"

namespace PrismaEngine
{
	class MeshRenderer
	{
	public:
		MeshRenderer(std::shared_ptr<const StaticMesh> mesh, const Material& matreial);

		void draw(const glm::mat4& model) const;

	private:
		std::shared_ptr<const StaticMesh> m_mesh;
		Material m_material;
	};
}