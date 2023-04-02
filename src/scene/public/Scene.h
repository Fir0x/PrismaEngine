#pragma once

#include <vector>

#include "Camera.h"
#include "PointLight.h"
#include "SceneObject.h"

namespace BerylEngine
{
	class Scene
	{
	public:
		size_t addObject(const SceneObject& object);
		void removeObject(size_t index);

		size_t addLight(const PointLight& light);
		void removeLight(size_t index);

		void render(const Camera& camera) const;

	private:
		std::vector<SceneObject> m_objects;
		std::vector<PointLight> m_lights;
	};
}