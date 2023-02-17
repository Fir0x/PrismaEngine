#include "meshUtilities.h"

#include <spdlog/spdlog.h>

namespace BerylEngine::MeshUtilities
{
	std::shared_ptr<StaticMesh> staticPlane(unsigned int subdivision)
	{
		std::vector<StaticMesh::Vertex> vertices;
		float start = (subdivision != 0 && subdivision % 2 == 0) ? -0.75f : -0.5f;
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
				indices.push_back(idx + 1);
				indices.push_back(idx);
				indices.push_back(idx + verticesPerLine + 1);

				// Left triangle
				indices.push_back(idx + verticesPerLine + 1);
				indices.push_back(idx);
				indices.push_back(idx + verticesPerLine);
			}
		}

		return std::make_shared<StaticMesh>(vertices, indices);
	}

	std::shared_ptr<StaticMesh> staticCube()
	{
		std::vector<StaticMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		{
			// Front face
			glm::vec3 normal(0.0f, 0.0f, 1.0f);
			StaticMesh::Vertex topLeft = { { -0.5f, 0.5f, 0.5f }, normal, { 0.0f, 0.33333f } };
			StaticMesh::Vertex topRight = { { 0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, 0.5f }, normal, { 0.0f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.0f } };

			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(3);
			indices.push_back(1);
		}

		{
			// Left face
			glm::vec3 normal(-1.0f, 0.0f, 0.0f);
			StaticMesh::Vertex topLeft = { { -0.5f, 0.5f, -0.5f }, normal, { 0.0f, 0.66666f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.66666f } };
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.33333f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };

			unsigned int offset = vertices.size();
			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(offset);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset);
			indices.push_back(offset + 3);
			indices.push_back(offset + 1);
		}

		{
			// Back face
			glm::vec3 normal(0.0f, 0.0f, -1.0f);
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, -0.5f }, normal, { 0.0f, 1.0f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, -0.5f }, normal, { 0.33333f, 1.0f } };
			StaticMesh::Vertex bottomLeft = { { 0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.66666f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, -0.5f, -0.5f }, normal, { 0.33333f, 0.66666f } };

			unsigned int offset = vertices.size();
			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(offset);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset);
			indices.push_back(offset + 3);
			indices.push_back(offset + 1);
		}

		{
			// Right face
			glm::vec3 normal(1.0f, 0.0f, 0.0f);
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.66666f } };
			StaticMesh::Vertex topRight = { { 0.5f, 0.5f, -0.5f }, normal, { 0.66666f, 0.66666f } };
			StaticMesh::Vertex bottomLeft = { { 0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, -0.5f }, normal, { 0.66666f, 0.33333f } };

			unsigned int offset = vertices.size();
			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(offset);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset);
			indices.push_back(offset + 3);
			indices.push_back(offset + 1);
		}

		{
			// Bottom face
			glm::vec3 normal(0.0f, -1.0f, 0.0f);
			StaticMesh::Vertex topLeft = { { -0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex topRight = { { 0.5f, -0.5f, 0.5f }, normal, { 0.66666f, 0.33333f } };
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, -0.5f }, normal, { 0.33333f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, -0.5f }, normal, { 0.66666f, 0.0f } };

			unsigned int offset = vertices.size();
			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(offset);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset);
			indices.push_back(offset + 3);
			indices.push_back(offset + 1);
		}

		{
			// Top face
			glm::vec3 normal(0.0f, 1.0f, 0.0f);
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, 0.5f }, normal, { 0.66666f, 0.33333f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, 0.5f }, normal, { 1.0f, 0.33333f } };
			StaticMesh::Vertex bottomLeft = { { 0.5f, 0.5f, -0.5f }, normal, { 0.66666f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, 0.5f, -0.5f }, normal, { 1.0f, 0.0f } };

			unsigned int offset = vertices.size();
			vertices.push_back(bottomLeft);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);
			vertices.push_back(bottomRight);

			indices.push_back(offset);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset);
			indices.push_back(offset + 3);
			indices.push_back(offset + 1);
		}

		return std::make_shared<StaticMesh>(vertices, indices);
	}
}