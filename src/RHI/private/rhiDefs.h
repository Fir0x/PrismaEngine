#pragma once

#include <GL/glew.h>

#include "../public/rhiDefs.h"

namespace BerylEngine
{
	GLenum usageType2GL(BufferUsageType usageType);
	GLenum accessType2GL(AccessType accessType);
}