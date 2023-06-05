#pragma once

#include "core/maths/public/Vector3.h"
#include "core/maths/public/Matrix4.h"

namespace PrismaEngine::ShaderDefs
{
	using vec3 = Vector3f;
	using mat4 = Matrix4f;

#include "../shaders/defines/structs.glsl"
}