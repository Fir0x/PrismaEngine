#pragma once

#include <vector>

#include "Camera.h"
#include "SceneObject.h"

namespace BerylEngine
{
	class Scene
	{
	public:
		size_t addObject(const SceneObject& object);
		void removeObject(size_t index);

		void render(Camera& camera);

	private:
		std::vector<SceneObject> m_objects;
	};
}