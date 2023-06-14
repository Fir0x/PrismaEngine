#include "../public/Transform.h"

#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Transform::Transform()
		: m_matrix(Matrix4f::identity())
	{
	}

	Transform::Transform(const Vector3f& position)
		: m_matrix(Matrix4f::identity())
	{
		translate(position);
	}

	void Transform::translate(const Vector3f& translation)
	{
		translate(translation.x, translation.y, translation.z);
	}

	void Transform::translate(float x, float y, float z)
	{
		Matrix4f translationMatrix = Matrix4f::identity();
		translationMatrix.data[3][0] = x;
		translationMatrix.data[3][1] = y;
		translationMatrix.data[3][2] = z;

		m_matrix = translationMatrix * m_matrix;
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
		rotationMatrix.data[0][0] = axis.x * axis.x * (1 - angleCos) + angleCos;
		rotationMatrix.data[0][1] = axis.x * axis.y * (1 - angleCos) + axis.z * angleSin;
		rotationMatrix.data[0][2] = axis.x * axis.z * (1 - angleCos) - axis.y * angleSin;

		rotationMatrix.data[1][0] = axis.x * axis.y * (1 - angleCos) - axis.z * angleSin;
		rotationMatrix.data[1][1] = axis.y * axis.y * (1 - angleCos) + angleCos;
		rotationMatrix.data[1][2] = axis.y * axis.z * (1 - angleCos) + axis.x * angleSin;

		rotationMatrix.data[2][0] = axis.x * axis.z * (1 - angleCos) + axis.y * angleSin;
		rotationMatrix.data[2][1] = axis.y * axis.z * (1 - angleCos) - axis.x * angleSin;
		rotationMatrix.data[2][2] = axis.z * axis.z * (1 - angleCos) + angleCos;

		return rotationMatrix * m;
	}

	void Transform::rotate(float angleX, float angleY, float angleZ)
	{
		Matrix3f rotation(m_matrix.getRow(0), m_matrix.getRow(1), m_matrix.getRow(2));
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
			rotation = rotateMatrixAroundAxis(rotation, getForward(), angleZ);

		if (angleY != 0)
			rotation = rotateMatrixAroundAxis(rotation, getUp(), angleY);

		if (angleX != 0)
			rotation = rotateMatrixAroundAxis(rotation, getRight(), angleX);

		setRotation(rotation);
	}

	void Transform::setRotation(const Matrix3f& rotation)
	{
		m_matrix.data[0][0] = rotation.data[0][0];
		m_matrix.data[0][1] = rotation.data[0][1];
		m_matrix.data[0][2] = rotation.data[0][2];

		m_matrix.data[1][0] = rotation.data[1][0];
		m_matrix.data[1][1] = rotation.data[1][1];
		m_matrix.data[1][2] = rotation.data[1][2];

		m_matrix.data[2][0] = rotation.data[2][0];
		m_matrix.data[2][1] = rotation.data[2][1];
		m_matrix.data[2][2] = rotation.data[2][2];
	}

	void Transform::scale(float factor)
	{
		scale(factor, factor, factor);
	}

	void Transform::scale(float scaleX, float scaleY, float scaleZ)
	{
		Matrix4f scaleMatrix = Matrix4f::identity();
		scaleMatrix.data[0][0] = scaleX;
		scaleMatrix.data[1][1] = scaleY;
		scaleMatrix.data[2][2] = scaleZ;

		m_matrix = scaleMatrix * m_matrix;
	}

	const Matrix4f& Transform::getMatrix() const
	{
		return m_matrix;
	}

	Vector3f Transform::getRight() const
	{
		return m_matrix.getColumn(0);
	}

	Vector3f Transform::getUp() const
	{
		return m_matrix.getColumn(1);
	}

	Vector3f Transform::getForward() const
	{
		return m_matrix.getColumn(2);
	}

	Vector3f Transform::getPosition() const
	{
		return m_matrix.getRow(3);
	}

	Matrix3f Transform::getRotation() const
	{
		return Matrix3f(m_matrix.getRow(0), m_matrix.getRow(1), m_matrix.getRow(2));
	}
}