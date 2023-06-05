#include "../public/Transform.h"

#include <glm/ext.hpp>

namespace PrismaEngine
{
	Transform::Transform()
	{
		m_transforms = Matrix4f(1.0f);
	}

	Transform::Transform(const Vector3f& position)
	{
		m_transforms = PrismaEngine::translate(Matrix4f(1.0f), position);
	}

	void Transform::translate(const Vector3f& translation)
	{
		m_transforms = PrismaEngine::translate(m_transforms, translation);
	}

	void Transform::rotate(float angleX, float angleY, float angleZ)
	{
		if (angleZ != 0)
		{
			Vector3f zAxis = getForward();
			m_transforms = PrismaEngine::rotate(m_transforms, angleZ, zAxis);
		}

		if (angleY != 0)
		{
			Vector3f yAxis = getUp();
			m_transforms = PrismaEngine::rotate(m_transforms, angleY, yAxis);
		}

		if (angleX != 0)
		{
			Vector3f xAxis = getRight();
			m_transforms = PrismaEngine::rotate(m_transforms, angleX, xAxis);
		}
	}

	void Transform::scale(float scaleX, float scaleY, float scaleZ)
	{
		m_transforms = PrismaEngine::scale(m_transforms, Vector3f(scaleX, scaleY, scaleZ));
	}

	void Transform::scale(float factor)
	{
		m_transforms = PrismaEngine::scale(m_transforms, Vector3f(factor));
	}

	const Matrix4f& Transform::getMatrix() const
	{
		return m_transforms;
	}

	const Vector3f Transform::getRight() const
	{
		return m_transforms.getColumn(0);
	}

	const Vector3f Transform::getUp() const
	{
		return m_transforms.getColumn(1);
	}

	const Vector3f Transform::getForward() const
	{
		return m_transforms.getColumn(2);
	}
}