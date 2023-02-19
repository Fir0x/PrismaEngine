#pragma once

#include "../core/StaticMesh.h"

namespace BerylEngine::MeshUtilities
{
	std::shared_ptr<StaticMesh> staticPlane(unsigned int subdivision = 0);
	std::shared_ptr<StaticMesh> staticCube();

	std::shared_ptr<StaticMesh> staticFromOBJ(const std::string& path);
}