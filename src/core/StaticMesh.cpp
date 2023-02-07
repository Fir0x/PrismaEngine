#include "StaticMesh.h"

#include <fstream>
#include <map>
#include <spdlog/spdlog.h>
#include <sstream>

namespace BerylEngine
{
	StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		m_vertices = vertices;
		m_indices = indices;
	}

	const std::vector<StaticMesh::Vertex>& StaticMesh::getData() const
	{
		return m_vertices;
	}

	size_t StaticMesh::triangleCount() const
	{
		return m_indices.size() / 3;
	}

	const std::vector<unsigned int>& StaticMesh::getIndices() const
	{
		return m_indices;
	}

	static std::vector<std::string> splitstr(const std::string& str, char delim)
	{
		std::vector<std::string> splitted;

		std::istringstream stream(str);
		std::string word;
		while (std::getline(stream, word, delim))
			splitted.push_back(word);

		return splitted;
	}

	std::optional<StaticMesh> StaticMesh::loadOBJFile(const std::string& path)
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

			spdlog::trace("Mesh loaded from {} contains {} vertices for {} triangles.",
						  path, mesh_vertices.size(), mesh_indices.size() / 3);

			return StaticMesh(mesh_vertices, mesh_indices);
		}
		else
		{
			spdlog::error("Failed to open OBJ file from {}", path);
			return std::optional<StaticMesh>();
		}
	}
}