#pragma once

#include "StaticMesh.h"

namespace PrismaEngine::MeshUtilities
{
	/**
	 * @brief Generate a static plane mesh.
	 * @return 
	*/
	std::shared_ptr<StaticMesh> staticPlane();
	/**
	 * @brief Generate a static cube mesh.
	 * @return 
	*/
	std::shared_ptr<StaticMesh> staticCube();
	/**
	 * @brief Generate a static sphere mesh.
	 * @param segmentCount Number of segment. Value is clamped as max(3, value).
	 * @param ringCount Number of ring. Value is clamped as max(3, value).
	 * @return
	*/
	std::shared_ptr<StaticMesh> staticSphere(unsigned int segmentCount, unsigned int ringCount);

	/**
	 * @brief Load a mesh from an OBJ file.
	 * @param path 
	 * @return 
	*/
	std::shared_ptr<StaticMesh> staticFromOBJ(const std::string& path);
}