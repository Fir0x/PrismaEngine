#pragma once

#include "Material.h"
#include "../geometry/StaticMesh.h"

namespace BerylEngine
{
	class MeshRenderer
	{
	private:
		std::shared_ptr<const StaticMesh> m_mesh;
		Material m_material;

	public:
		MeshRenderer(std::shared_ptr<const StaticMesh> mesh, const Material& matreial);

		void draw(const glm::mat4& model) const;
	};
}