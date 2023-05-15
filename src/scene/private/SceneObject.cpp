#include "../public/SceneObject.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

namespace PrismaEngine
{
	SceneObject::SceneObject(const MeshRenderer& renderer)
		: m_transform(), m_renderer(renderer)
	{
	}

	SceneObject::SceneObject(const Vec3f& pos, const MeshRenderer& renderer)
		: m_transform(pos), m_renderer(renderer)
	{
	}

	Mat3f SceneObject::processNormalMatrix(const Mat4f& model, const Mat4f& view) const
	{
		return Mat3f(transpose(inverse(view * model)));
	}

	Transform& SceneObject::transform()
	{
		return m_transform;
	}

	void SceneObject::draw() const
	{
		Mat4f model = m_transform.getMatrix();
		m_renderer.draw(model);
	}
}