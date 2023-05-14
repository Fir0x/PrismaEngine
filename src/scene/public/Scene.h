#pragma once

#include <vector>

#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SceneObject.h"
#include "core/maths/public/vec2i.h"

namespace PrismaEngine
{
	class Scene
	{
	public:
		size_t addObject(const SceneObject& object);
		void removeObject(size_t index);

		size_t addLight(const DirectionalLight& light);
		size_t addLight(const PointLight& light);

		void drawGeometry(const Camera& camera, const Vec2i& windowSizes) const;
		void drawLights(const Camera& camera, const Vec2i& windowSizes) const;

	private:
		std::vector<SceneObject> m_objects;
		std::vector<DirectionalLight> m_directionaLights;
		std::vector<PointLight> m_pointLights;
	};
}