#pragma once

#include "StaticMesh.h"

namespace BerylEngine::MeshUtilities
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
	 * @brief Load a mesh from an OBJ file.
	 * @param path 
	 * @return 
	*/
	std::shared_ptr<StaticMesh> staticFromOBJ(const std::string& path);
}