#include "../public/Transform.h"

#include <glm/ext.hpp>

namespace PrismaEngine
{
	Transform::Transform()
	{
		m_transforms = glm::mat4(1.0f);
	}

	Transform::Transform(const Vec3f& position)
	{
		m_transforms = glm::translate(glm::mat4(1.0f), position);
	}

	void Transform::translate(const Vec3f& translation)
	{
		m_transforms = glm::translate(m_transforms, translation);
	}

	void Transform::rotate(float angleX, float angleY, float angleZ)
	{
		if (angleZ != 0)
		{
			Vec3f zAxis = getForward();
			m_transforms = glm::rotate(m_transforms, angleZ, zAxis);
		}

		if (angleY != 0)
		{
			Vec3f yAxis = getUp();
			m_transforms = glm::rotate(m_transforms, angleY, yAxis);
		}

		if (angleX != 0)
		{
			Vec3f xAxis = getRight();
			m_transforms = glm::rotate(m_transforms, angleX, xAxis);
		}
	}

	void Transform::scale(float scaleX, float scaleY, float scaleZ)
	{
		m_transforms = glm::scale(m_transforms, Vec3f(scaleX, scaleY, scaleZ));
	}

	void Transform::scale(float factor)
	{
		m_transforms = glm::scale(m_transforms, Vec3f(factor));
	}

	const glm::mat4& Transform::getMatrix() const
	{
		return m_transforms;
	}

	const Vec3f Transform::getRight() const
	{
		return glm::column(m_transforms, 0);
	}

	const Vec3f Transform::getUp() const
	{
		return glm::column(m_transforms, 1);
	}

	const Vec3f Transform::getForward() const
	{
		return glm::column(m_transforms, 2);
	}
}