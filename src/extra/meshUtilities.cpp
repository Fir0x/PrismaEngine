#include "meshUtilities.h"

#include <fstream>
#include <map>
#include <spdlog/spdlog.h>
#include <sstream>

namespace BerylEngine::MeshUtilities
{
	static glm::vec4 processTangentData(const StaticMesh::Vertex& v1, const StaticMesh::Vertex& v2,
										const StaticMesh::Vertex& v3)
	{
		glm::vec3 edge1 = v2.coords - v1.coords;
		glm::vec3 edge2 = v3.coords - v1.coords;
		glm::vec2 deltaUV1 = v2.uvs - v1.uvs;
		glm::vec2 deltaUV2 = v3.uvs - v1.uvs;
		
		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		glm::vec3 tangent;
		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent = glm::normalize(tangent);

		glm::vec3 bitangent;
		bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent = glm::normalize(bitangent);

		float bitangentSign = glm::dot(glm::cross(tangent, bitangent), v1.normals);

		return glm::vec4(tangent, bitangentSign);
	}

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

			unsigned int offset = (unsigned int)vertices.size();
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

			unsigned int offset = (unsigned int)vertices.size();
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

			unsigned int offset = (unsigned int)vertices.size();
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

			unsigned int offset = (unsigned int)vertices.size();
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

			unsigned int offset = (unsigned int)vertices.size();
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
	std::shared_ptr<StaticMesh> staticFromOBJ(const std::string& path)
	{
		std::ifstream stream;
		stream.open(path);

		if (stream.is_open())
		{
			bool secondMesh = false;

			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> uvs;

			std::vector<StaticMesh::Vertex> mesh_vertices;
			std::vector<unsigned int> mesh_indices;

			struct VertexInfo
			{
				int vertIdx;
				int normIdx;
				int uvIdx;

				bool operator<(const VertexInfo& rhs) const
				{
					return std::tie(vertIdx, normIdx, uvIdx) < std::tie(rhs.vertIdx, rhs.normIdx, rhs.uvIdx);
				}
			};
			std::map<VertexInfo, int> indexMapper;

			std::string line;
			while (std::getline(stream, line))
			{
				if (line[0] == '#')
					continue;

				auto splitted = splitstr(line, ' ');
				if (line[0] == 'o')
				{
					if (secondMesh)
					{
						spdlog::warn("{} contained more than one mesh definition. Only the first one was parsed.");
						break;
					}
				}
				else if (line[0] == 'v')
				{
					if (line[1] == 't')
					{
						uvs.push_back({
							std::stof(splitted[1]),
							std::stof(splitted[2])
							});
					}
					else if (line[1] == 'n')
					{
						normals.push_back({
							std::stof(splitted[1]),
							std::stof(splitted[2]),
							std::stof(splitted[3])
							});
					}
					else
					{
						vertices.push_back({
							std::stof(splitted[1]),
							std::stof(splitted[2]),
							std::stof(splitted[3])
							});
					}
				}
				else if (line[0] == 'f')
				{
					for (int i = 1; i < 4; i++)
					{
						auto indices = splitstr(splitted[i], '/');
						int vertIdx = std::stoi(indices[0]) - 1;
						int uvIdx = std::stoi(indices[1]) - 1;
						int normIdx = std::stoi(indices[2]) - 1;
						VertexInfo vInfo = { vertIdx, uvIdx, normIdx };

						if (indexMapper.find(vInfo) == indexMapper.end())
						{
							glm::vec3 v = vertices.at(vertIdx);
							glm::vec3 n = normals.at(normIdx);
							glm::vec2 uv = uvs.at(uvIdx);

							mesh_vertices.push_back({ v, n, uv });
							int vertexIndex = int(mesh_vertices.size()) - 1;
							mesh_indices.push_back(vertexIndex);
							indexMapper.insert({ vInfo, vertexIndex });
						}
						else
						{
							mesh_indices.push_back(indexMapper[vInfo]);
						}
					}
				}
			}

			spdlog::trace("Mesh loaded from {}.", path);

			return std::make_shared<StaticMesh>(mesh_vertices, mesh_indices);
		}
		else
		{
			spdlog::error("Failed to open OBJ file from {}", path);
			return nullptr;
		}
	}
}