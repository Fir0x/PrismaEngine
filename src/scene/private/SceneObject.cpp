#include "../public/SceneObject.h"

#include <GL/glew.h>

namespace PrismaEngine
{
	SceneObject::SceneObject(const MeshRenderer& renderer)
		: m_transform(), m_renderer(renderer)
	{
	}

	SceneObject::SceneObject(const Vector3f& pos, const MeshRenderer& renderer)
		: m_transform(pos), m_renderer(renderer)
	{
	}

	Matrix3f SceneObject::processNormalMatrix(const Matrix4f& model, const Matrix4f& view) const
	{
		return (view * model).inverse().transpose().toMatrix3();
	}

	Transform& SceneObject::transform()
	{
		return m_transform;
	}

	void SceneObject::draw() const
	{
		Matrix4f model = m_transform.getMatrix();
		m_renderer.draw(model);
	}
}