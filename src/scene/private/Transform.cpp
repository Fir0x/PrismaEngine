#include "../public/Transform.h"

#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Transform::Transform()
		: m_position(Vector3f::zero()),
		m_quaternion(Quaternion::identity()),
		m_scale(Vector3f::one())
	{
	}

	Transform::Transform(const Vector3f& position)
		: m_position(position),
		m_quaternion(Quaternion::identity()),
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
		m_quaternion = Quaternion::fromEuler(angleX, angleY, angleZ) * m_quaternion;
	}

	void Transform::setRotation(float angleX, float angleY, float angleZ)
	{
		m_quaternion = Quaternion::fromEuler(angleX, angleY, angleZ);
	}

	void Transform::setRotation(const Vector3f& right, const Vector3f& up, const Vector3f& forward)
	{
		Matrix3f rotationMatrix(right, up, forward);
		m_quaternion = Quaternion(rotationMatrix);
	}

	void Transform::setRotation(const Matrix3f& rotationMatrix)
	{
		m_quaternion = Quaternion(rotationMatrix);
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
		Vector3f scaledRight = m_scale * m_quaternion.getRotatedRight();
		Vector3f scaledUp = m_scale * m_quaternion.getRotatedUp();
		Vector3f scaledForward = m_scale * m_quaternion.getRotatedForward();

		return Matrix4f(scaledRight, scaledUp, scaledForward, Vector4f(m_position, 1.0f));
	}

	Vector3f Transform::getRight() const
	{
		return m_quaternion.getRotatedRight();
	}

	Vector3f Transform::getUp() const
	{
		return m_quaternion.getRotatedUp();
	}

	Vector3f Transform::getForward() const
	{
		return m_quaternion.getRotatedForward();
	}

	const Vector3f& Transform::getPosition() const
	{
		return m_position;
	}

	Matrix3f Transform::getRotation() const
	{
		return m_quaternion.toMatrix();
	}

	const Vector3f& Transform::getScale() const
	{
		return m_scale;
	}

	Transform Transform::getInverse() const
	{
		Transform result;
		result.m_quaternion = m_quaternion.inverse();
		result.m_scale = 1.0f / m_scale;
		result.m_position = Vector3f(-m_quaternion.getRotatedRight().dot(m_position),
			-m_quaternion.getRotatedUp().dot(m_position),
			-m_quaternion.getRotatedForward().dot(m_position)) * result.m_scale;

		return result;
	}

	Vector3f Transform::transformPoint(const Matrix4f& m, const Vector3f& p)
	{
		Vector3f x = m.getRow(0) * p.x;
		Vector3f y = m.getRow(1) * p.y;
		Vector3f z = m.getRow(2) * p.z;
		Vector3f w = m.getRow(3);

		return x + y + z + w;
	}

	Vector3f Transform::transformDirection(const Matrix4f& m, const Vector3f& direction)
	{
		Vector3f x = m.getRow(0) * direction.x;
		Vector3f y = m.getRow(1) * direction.y;
		Vector3f z = m.getRow(2) * direction.z;

		return x + y + z;
	}
}