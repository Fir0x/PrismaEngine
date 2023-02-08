#include "meshUtilities.h"

#include <spdlog/spdlog.h>

namespace BerylEngine::MeshUtilities
{
	std::shared_ptr<StaticMesh> staticPlane(unsigned int subdivision)
	{
		std::vector<StaticMesh::Vertex> vertices;
		float start = subdivision % 2 == 0 ? -0.75f : -0.5f;
		float offset = subdivision == 0 ? 1.0f : 1 / float(subdivision);
		for (unsigned int i = 0; i < subdivision + 2; i++)
		{
			for (unsigned int j = 0; j < subdivision + 2; j++)
			{
				StaticMesh::Vertex vertex;
				vertex.coords = glm::vec3(start + offset * j, 0.0f, start + offset * i);
				vertex.normals = glm::vec3(0.0f, 1.0f, 0.0f);
				vertex.uvs = glm::vec2(offset * j, offset * i);

				vertices.push_back(vertex);
			}
		}

		std::vector<unsigned int> indices;
		unsigned int verticesPerLine = subdivision + 2;
		for (unsigned int i = 0; i < subdivision + 1; i++)
		{
			for (unsigned int j = 0; j < subdivision + 1; j++)
			{
				unsigned int idx = i * verticesPerLine + j;
				// Right triangle
				indices.push_back(idx);
				indices.push_back(idx + 1);
				indices.push_back(idx + verticesPerLine + 1);

				// Left triangle
				indices.push_back(idx);
				indices.push_back(idx + verticesPerLine + 1);
				indices.push_back(idx + verticesPerLine);
			}
		}

		return std::make_shared<StaticMesh>(vertices, indices);
	}
}