#include "StaticMesh.h"

#include <fstream>
#include <map>
#include <spdlog/spdlog.h>
#include <sstream>

#include "glErrors.h"
#include "utils.h"

namespace BerylEngine
{
	StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: m_vbo(vertices.data(), vertices.size())
	{
		VertexBufferLayout layout;
		layout.Add<float>(3);
		layout.Add<float>(3);
		layout.Add<float>(2);

		m_vao = std::make_unique<VertexArray>(m_vbo, layout);
		m_ibo = std::make_unique<TypedBuffer<unsigned int>>(indices.data(), indices.size());

		spdlog::trace("Static mesh created with {} vertices for {} triangles.",
						vertices.size(), indices.size() / 3);
	}

	std::shared_ptr<StaticMesh> StaticMesh::fromOBJFile(const std::string& path)
	{
		std::ifstream stream;
		stream.open(path);

		if (stream.is_open())
		{
			bool secondMesh = false;

			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> uvs;

			std::vector<Vertex> mesh_vertices;
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

	void StaticMesh::draw() const
	{
		m_vao->bind();
		m_ibo->bind(BufferUsageType::IndexBuffer);
		GL_CALL(glDrawElements(GL_TRIANGLES, m_ibo->getCount(), GL_UNSIGNED_INT, nullptr));
	}
}