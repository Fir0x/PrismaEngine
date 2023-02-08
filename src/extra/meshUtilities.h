#pragma once

#include "../core/StaticMesh.h"

namespace BerylEngine::MeshUtilities
{
	std::shared_ptr<StaticMesh> staticPlane(unsigned int subdivision = 0);
}