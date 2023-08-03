#include "../public/Transform.h"

#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Transform::Transform()
		: m_position(Vector3f::zero()),
		m_right(Vector3f::right()),
		m_up(Vector3f::up()),
		m_forward(Vector3f::forward()),
		m_scale(Vector3f::one())
	{
	}

	Transform::Transform(const Vector3f& position)
		: m_position(position),
		m_right(Vector3f::right()),
		m_up(Vector3f::up()),
		m_forward(Vector3f::forward()),
		m_scale(Vector3f::one())
	{
	}

	void Transform::translate(const Vector3f& translation)
	{
		m_position += translation;
	}

	void Transform::translate(float x, float y, float z)
	{
		translate(Vector3f(x, y, z));
	}

	/**
	 * @brief 
	 * @param m 
	 * @param axis 
	 * @param angle Rotation angle in degrees
	 * @return 
	*/
	static Matrix3f rotateMatrixAroundAxis(const Matrix3f& m, const Vector3f& axis, const float angle)
	{
		const float angleCos = cos(degreesToRadians(angle));
		const float angleSin = sin(degreesToRadians(angle));

		Matrix3f rotationMatrix;
		Vector3f tmp = (1.0f - angleCos) * axis;
		rotationMatrix.data[0][0] = axis.x * tmp.x + angleCos;
		rotationMatrix.data[0][1] = axis.x * tmp.y + axis.z * angleSin;
		rotationMatrix.data[0][2] = axis.x * tmp.z - axis.y * angleSin;

		rotationMatrix.data[1][0] = axis.y * tmp.x - axis.z * angleSin;
		rotationMatrix.data[1][1] = axis.y * tmp.y + angleCos;
		rotationMatrix.data[1][2] = axis.y * tmp.z + axis.x * angleSin;

		rotationMatrix.data[2][0] = axis.z * tmp.x + axis.y * angleSin;
		rotationMatrix.data[2][1] = axis.z * tmp.y - axis.x * angleSin;
		rotationMatrix.data[2][2] = axis.z * tmp.z + angleCos;

		return rotationMatrix * m;
	}

	void Transform::rotate(float angleX, float angleY, float angleZ)
	{
		Matrix3f rotation(m_right, m_up, m_forward);
		if (angleZ != 0)
			rotation = rotateMatrixAroundAxis(rotation, getForward(), angleZ);

		if (angleY != 0)
			rotation = rotateMatrixAroundAxis(rotation, getUp(), angleY);

		if (angleX != 0)
			rotation = rotateMatrixAroundAxis(rotation, getRight(), angleX);

		setRotation(rotation);
	}

	void Transform::setRotation(float angleX, float angleY, float angleZ)
	{
		Matrix3f rotation = Matrix3f::identity();
		if (angleZ != 0)
			rotation = rotateMatrixAroundAxis(rotation, Vector3f(0.0f, 0.0f, 1.0f), angleZ);

		if (angleY != 0)
			rotation = rotateMatrixAroundAxis(rotation, Vector3f(0.0f, 1.0f, 0.0f), angleY);

		if (angleX != 0)
			rotation = rotateMatrixAroundAxis(rotation, Vector3f(1.0f, 0.0f, 0.0f), angleX);

		setRotation(rotation);
	}

	void Transform::setRotation(const Vector3f& right, const Vector3f& up, const Vector3f& forward)
	{
		m_right = right;
		m_up = up;
		m_forward = forward;
	}

	void Transform::setRotation(const Matrix3f& rotationMatrix)
	{
		m_right = rotationMatrix.getRow(0);
		m_up = rotationMatrix.getRow(1);
		m_forward = rotationMatrix.getRow(2);
	}

	void Transform::scale(float factor)
	{
		scale(factor, factor, factor);
	}

	void Transform::scale(float scaleX, float scaleY, float scaleZ)
	{
		m_scale *= Vector3f(scaleX, scaleY, scaleZ);
	}

	Matrix4f Transform::getMatrix() const
	{
		Vector3f scaledRight = m_scale * m_right;
		Vector3f scaledUp = m_scale * m_up;
		Vector3f scaledForward = m_scale * m_forward;

		return Matrix4f(scaledRight, scaledUp, scaledForward, Vector4f(m_position, 1.0f));
	}

	const Vector3f& Transform::getRight() const
	{
		return m_right;
	}

	const Vector3f& Transform::getUp() const
	{
		return m_up;
	}

	const Vector3f& Transform::getForward() const
	{
		return m_forward;
	}

	const Vector3f& Transform::getPosition() const
	{
		return m_position;
	}

	Matrix3f Transform::getRotation() const
	{
		return Matrix3f(m_right, m_up, m_forward);
	}

	const Vector3f& Transform::getScale() const
	{
		return m_scale;
	}

	Transform Transform::getInverse() const
	{
		Transform result;
		result.m_right = Vector3f(m_right.x, m_up.x, m_forward.x);
		result.m_up = Vector3f(m_right.y, m_up.y, m_forward.y);
		result.m_forward = Vector3f(m_right.z, m_up.z, m_forward.z);
		result.m_scale = 1.0f / m_scale;
		result.m_position = Vector3f(-m_right.dot(m_position), -m_up.dot(m_position), -m_forward.dot(m_position)) * result.m_scale;

		return result;
	}
}