#include "../public/meshUtilities.h"

#include <fstream>
#include <map>
#include <spdlog/spdlog.h>
#include <sstream>

#include "core/maths/public/vector.h"
#include "core/maths/public/vec2f.h"
#include "core/maths/public/vec3f.h"
#include "core/maths/public/vec4f.h"

namespace PrismaEngine::MeshUtilities
{
#define DEG2RAD 0.017453292519943295

	static Vec4f processTangentData(const StaticMesh::Vertex& v1, const StaticMesh::Vertex& v2,
										const StaticMesh::Vertex& v3)
	{
		Vec3f edge1 = v2.position - v1.position;
		Vec3f edge2 = v3.position - v1.position;
		Vec2f deltaUV1 = v2.uvs - v1.uvs;
		Vec2f deltaUV2 = v3.uvs - v1.uvs;
		
		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		Vec3f tangent;
		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent = normalize(tangent);

		Vec3f bitangent;
		bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent = normalize(bitangent);

		float bitangentSign = dot(cross(tangent, bitangent), v1.normal);

		return Vec4f(tangent, bitangentSign);
	}

	std::shared_ptr<StaticMesh> staticPlane()
	{
		std::vector<StaticMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		Vec3f normal(0.0f, 1.0f, 0.0f);
		StaticMesh::Vertex bottomLeft = { { -0.5f, 0.0f, 0.5f }, normal, { 0.0f, 0.0f } };
		StaticMesh::Vertex bottomRight = { { 0.5f, 0.0f, 0.5f }, normal, { 1.0f, 0.0f } };
		StaticMesh::Vertex topLeft = { { -0.5f, 0.0f, -0.5f }, normal, { 0.0f, 1.0f } };
		StaticMesh::Vertex topRight = { { 0.5f, 0.0f, -0.5f }, normal, { 1.0f, 1.0f } };

		Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
		bottomLeft.tangentData = tangentData;
		bottomRight.tangentData = tangentData;
		topLeft.tangentData = tangentData;
		topRight.tangentData = tangentData;

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

		return std::make_shared<StaticMesh>(vertices, indices);
	}

	std::shared_ptr<StaticMesh> staticCube()
	{
		std::vector<StaticMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		{
			// Front face
			Vec3f normal(0.0f, 0.0f, 1.0f);
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, 0.5f }, normal, { 0.0f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.0f } };
			StaticMesh::Vertex topLeft = { { -0.5f, 0.5f, 0.5f }, normal, { 0.0f, 0.33333f } };
			StaticMesh::Vertex topRight = { { 0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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
			Vec3f normal(-1.0f, 0.0f, 0.0f);
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.33333f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex topLeft = { { -0.5f, 0.5f, -0.5f }, normal, { 0.0f, 0.66666f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.66666f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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
			Vec3f normal(0.0f, 0.0f, -1.0f);
			StaticMesh::Vertex bottomLeft = { { 0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.66666f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, -0.5f, -0.5f }, normal, { 0.33333f, 0.66666f } };
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, -0.5f }, normal, { 0.0f, 1.0f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, -0.5f }, normal, { 0.33333f, 1.0f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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
			Vec3f normal(1.0f, 0.0f, 0.0f);
			StaticMesh::Vertex bottomLeft = { { 0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, -0.5f }, normal, { 0.66666f, 0.33333f } };
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, 0.5f }, normal, { 0.33333f, 0.66666f } };
			StaticMesh::Vertex topRight = { { 0.5f, 0.5f, -0.5f }, normal, { 0.66666f, 0.66666f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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
			Vec3f normal(0.0f, -1.0f, 0.0f);
			StaticMesh::Vertex bottomLeft = { { -0.5f, -0.5f, -0.5f }, normal, { 0.33333f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { 0.5f, -0.5f, -0.5f }, normal, { 0.66666f, 0.0f } };
			StaticMesh::Vertex topLeft = { { -0.5f, -0.5f, 0.5f }, normal, { 0.33333f, 0.33333f } };
			StaticMesh::Vertex topRight = { { 0.5f, -0.5f, 0.5f }, normal, { 0.66666f, 0.33333f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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
			Vec3f normal(0.0f, 1.0f, 0.0f);
			StaticMesh::Vertex bottomLeft = { { 0.5f, 0.5f, -0.5f }, normal, { 0.66666f, 0.0f } };
			StaticMesh::Vertex bottomRight = { { -0.5f, 0.5f, -0.5f }, normal, { 1.0f, 0.0f } };
			StaticMesh::Vertex topLeft = { { 0.5f, 0.5f, 0.5f }, normal, { 0.66666f, 0.33333f } };
			StaticMesh::Vertex topRight = { { -0.5f, 0.5f, 0.5f }, normal, { 1.0f, 0.33333f } };

			Vec4f tangentData = processTangentData(bottomLeft, topRight, topLeft);
			bottomLeft.tangentData = tangentData;
			bottomRight.tangentData = tangentData;
			topLeft.tangentData = tangentData;
			topRight.tangentData = tangentData;

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

	std::shared_ptr<StaticMesh> staticSphere(unsigned int segmentCount, unsigned int ringCount)
	{
		if (segmentCount < 3)
			segmentCount = 3;

		if (ringCount < 3)
			ringCount = 3;

		std::vector<StaticMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		const float horizontalUVShift = 1.0f / float(segmentCount);
		const float verticalUVShift = 1.0f / float(ringCount);

		// TODO
		// Process tangents

		// South pole
		{
			Vec3f position(0.0f, -1.0f, 0.0f);
			float u = horizontalUVShift / 2.0f;
			for (unsigned int segment = 0; segment < segmentCount; segment++)
			{
				StaticMesh::Vertex vertex = { position, position, { u, 0.0f } };
				vertices.push_back(vertex);

				u += horizontalUVShift;
			}
		}

		const float shiftTheta = 360.0f / float(segmentCount);
		const float shiftPhi = 180.0f / float(ringCount);

		// Bottom ring
		{
			const float phi = 180.0f - shiftPhi;

			const float y = cos(phi * DEG2RAD);
			const float v = verticalUVShift;
			{
				const float x = sin(phi * DEG2RAD);
				const float z = 0.0f;

				StaticMesh::Vertex vertex = { { x, y, z}, {x, y, z}, { 0.0f , v } };
				vertices.push_back(vertex);
			}

			for (unsigned int segment = 1; segment <= segmentCount; segment++)
			{
				const float theta = 360.0f - segment * shiftTheta;
				const float x = sin(phi * DEG2RAD) * cos(theta * DEG2RAD);
				const float z = sin(phi * DEG2RAD) * sin(theta * DEG2RAD);
				const float u = segment * horizontalUVShift;

				StaticMesh::Vertex vertex = { { x, y, z}, {x, y, z}, { u, v } };
				vertices.push_back(vertex);

				// Ring creation
				unsigned int rightIndex = vertices.size() - 1;
				unsigned int leftIndex = rightIndex - 1;
				unsigned int poleIndex = leftIndex - segmentCount;

				indices.push_back(leftIndex);
				indices.push_back(poleIndex);
				indices.push_back(rightIndex);
			}
		}

		// Intermediate rings
		{
			float phi = 180.0f - shiftPhi * 2.0f;

			for (unsigned int ring = 1; ring < ringCount - 1; ring++)
			{
				const float y = cos(phi * DEG2RAD);
				const float v = (ring + 1) * verticalUVShift;
				{
					const float x = sin(phi * DEG2RAD);
					const float z = 0.0f;

					StaticMesh::Vertex vertex = { { x, y, z}, {x, y, z}, { 0.0f , v } };
					vertices.push_back(vertex);
				}

				for (unsigned int segment = 1; segment <= segmentCount; segment++)
				{
					const float theta = 360.0f - segment * shiftTheta;
					const float x = sin(phi * DEG2RAD) * cos(theta * DEG2RAD);
					const float z = sin(phi * DEG2RAD) * sin(theta * DEG2RAD);
					const float u = segment * horizontalUVShift;

					StaticMesh::Vertex vertex = { { x, y, z}, {x, y, z}, { u, v } };
					vertices.push_back(vertex);

					// Ring creation
					unsigned int topRightIndex = vertices.size() - 1;
					unsigned int topLeftIndex = topRightIndex - 1;
					unsigned int bottomLeftIndex = topLeftIndex - segmentCount - 1;
					unsigned int bottomRightIndex = bottomLeftIndex + 1;

					indices.push_back(topLeftIndex);
					indices.push_back(bottomLeftIndex);
					indices.push_back(bottomRightIndex);

					indices.push_back(bottomRightIndex);
					indices.push_back(topRightIndex);
					indices.push_back(topLeftIndex);
				}

				phi -= shiftPhi;
			}
		}

		// North pole + top ring
		{
			Vec3f position(0.0f, 1.0f, 0.0f);
			float u = horizontalUVShift / 2.0f;
			for (unsigned int segment = 0; segment < segmentCount; segment++)
			{
				StaticMesh::Vertex vertex = { position, position, { u, 1.0f } };
				vertices.push_back(vertex);

				// Ring creation
				unsigned int poleIndex = vertices.size() - 1;
				unsigned int rightIndex = poleIndex - segmentCount;
				unsigned int leftIndex = rightIndex - 1;

				indices.push_back(rightIndex);
				indices.push_back(poleIndex);
				indices.push_back(leftIndex);

				u += horizontalUVShift;
			}
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

			std::vector<Vec3f> vertices;
			std::vector<Vec3f> normals;
			std::vector<Vec2f> uvs;

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
							Vec3f v = vertices.at(vertIdx);
							Vec3f n = normals.at(normIdx);
							Vec2f uv = uvs.at(uvIdx);

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