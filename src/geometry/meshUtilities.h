#pragma once

#include "StaticMesh.h"

namespace BerylEngine::MeshUtilities
{
	std::shared_ptr<StaticMesh> staticPlane();
	std::shared_ptr<StaticMesh> staticCube();

	std::shared_ptr<StaticMesh> staticFromOBJ(const std::string& path);
}