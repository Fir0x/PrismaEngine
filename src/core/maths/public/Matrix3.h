#pragma once

#include "Vector3.h"

namespace PrismaEngine
{
	template<typename T>
	class Matrix3
	{
	public:
		Matrix3() = default;

		Matrix3(const T& x)
		{
			data[0][0] = x;
			data[0][1] = static_cast<T>(0);
			data[0][2] = static_cast<T>(0);

			data[1][0] = static_cast<T>(0);
			data[1][1] = x;
			data[1][2] = static_cast<T>(0);

			data[2][0] = static_cast<T>(0);
			data[2][1] = static_cast<T>(0);
			data[2][2] = x;
		}

		Matrix3(const Vector3<T>& row0, const Vector3<T>& row1, const Vector3<T>& row2)
		{
			data[0][0] = row0.x;
			data[0][1] = row0.y;
			data[0][2] = row0.z;

			data[1][0] = row1.x;
			data[1][1] = row1.y;
			data[1][2] = row1.z;

			data[2][0] = row2.x;
			data[2][1] = row2.y;
			data[2][2] = row2.z;
		}

		static Matrix3<T> fromPlane(const Vector3<T>& xPlane, const Vector3<T>& yPlane, const Vector3<T>& zPlane)
		{
			Matrix3<T> result;

			result.data[0][0] = xPlane.x;
			result.data[0][1] = yPlane.x;
			result.data[0][2] = zPlane.x;

			result.data[1][0] = xPlane.y;
			result.data[1][1] = yPlane.y;
			result.data[1][2] = zPlane.y;

			result.data[2][0] = xPlane.z;
			result.data[2][1] = yPlane.z;
			result.data[2][2] = zPlane.z;

			return result;
		}

		static Matrix3<T> identity()
		{
			return Matrix3<T>(static_cast<T>(1));
		}

		T determinant() const
		{
			const float factor1 = data[1][0] * data[2][1] - data[1][1] * data[2][0];
			const float factor2 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
			const float factor3 = data[1][1] * data[2][2] - data[2][1] * data[1][2];

			 return data[0][0] * factor3 - data[0][1] * factor2 + data[0][2] * factor1;
		}

		Matrix3<T> transpose() const
		{
			Vector3<T> x(data[0][0], data[0][1], data[0][2]);
			Vector3<T> y(data[1][0], data[1][1], data[1][2]);
			Vector3<T> z(data[2][0], data[2][1], data[2][2]);
			
			return fromPlane(x, y, z);
		}

		Matrix3<T> inverse() const
		{
			T adjugateX0 = +(data[1][1] * data[2][2] - data[1][2] * data[2][1]);
			T adjugateX1 = -(data[1][0] * data[2][2] - data[1][2] * data[2][0]);
			T adjugateX2 = +(data[1][0] * data[2][1] - data[1][1] * data[2][0]);

			T adjugateY0 = -(data[0][1] * data[2][2] - data[0][2] * data[2][1]);
			T adjugateY1 = +(data[0][0] * data[2][2] - data[0][2] * data[2][0]);
			T adjugateY2 = -(data[0][0] * data[2][1] - data[0][1] * data[2][0]);

			T adjugateZ0 = +(data[0][1] * data[1][2] - data[0][2] * data[1][1]);
			T adjugateZ1 = -(data[0][0] * data[1][2] - data[0][2] * data[1][0]);
			T adjugateZ2 = +(data[0][0] * data[1][1] - data[0][1] * data[1][0]);

			T determinant = data[0][0] * adjugateX0 + data[0][1] * adjugateX1 + data[0][2] * adjugateX2;
			T oneOverDeterminant = static_cast<T>(1) / determinant;

			Vector3<T> inverseX = oneOverDeterminant * Vector3<T>(adjugateX0, adjugateX1, adjugateX2);
			Vector3<T> inverseY = oneOverDeterminant * Vector3<T>(adjugateY0, adjugateY1, adjugateY2);
			Vector3<T> inverseZ = oneOverDeterminant * Vector3<T>(adjugateZ0, adjugateZ1, adjugateZ2);

			return fromPlane(inverseX, inverseY, inverseZ);
		}

		Vector3<T> getColumn(int index) const
		{
			return Vector3<T>(data[0][index], data[1][index], data[2][index]);
		}

		Vector3<T> getRow(int index) const
		{
			const T* row = data[index];
			return Vector3<T>(row[0], row[1], row[2]);
		}

		const T& getValue(int row, int column) const
		{
			return data[row][column];
		}

		void setValue(int row, int column, T value)
		{
			data[row][column] = value;
		}

		Matrix3<T> operator+(const Matrix3<T>& rhs) const
		{
			Vector3<T> row0 = getRow(0) + rhs.getRow(0);
			Vector3<T> row1 = getRow(1) + rhs.getRow(1);
			Vector3<T> row2 = getRow(2) + rhs.getRow(2);

			return Matrix3<T>(row0, row1, row2);
		}

		Matrix3<T> operator-(const Matrix3<T>& rhs) const
		{
			Vector3<T> row0 = getRow(0) - rhs.getRow(0);
			Vector3<T> row1 = getRow(1) - rhs.getRow(1);
			Vector3<T> row2 = getRow(2) - rhs.getRow(2);

			return Matrix3<T>(row0, row1, row2);
		}

		Matrix3<T> operator*(const Matrix3<T>& rhs) const
		{
			Vector3<T> row0 = Vector3<T>(data[0][0]) * rhs.getRow(0);
			row0 += Vector3<T>(data[0][1]) * rhs.getRow(1);
			row0 += Vector3<T>(data[0][2]) * rhs.getRow(2);

			Vector3<T> row1 = Vector3<T>(data[1][0]) * rhs.getRow(0);
			row1 += Vector3<T>(data[1][1]) * rhs.getRow(1);
			row1 += Vector3<T>(data[1][2]) * rhs.getRow(2);

			Vector3<T> row2 = Vector3<T>(data[2][0]) * rhs.getRow(0);
			row2 += Vector3<T>(data[2][1]) * rhs.getRow(1);
			row2 += Vector3<T>(data[2][2]) * rhs.getRow(2);

			return Matrix3<T>(row0, row1, row2);
		}

		Vector3<T> operator*(const Vector3<T>& rhs) const
		{
			T x = getRow(0).dot(rhs);
			T y = getRow(1).dot(rhs);
			T z = getRow(2).dot(rhs);

			return Vector3<T>(x, y, z);
		}

		bool operator==(const Matrix3<T>& rhs) const
		{
			for (int row = 0; row < 3; row++)
			{
				for (int column = 0; column < 3; column++)
				{
					if (data[row][column] != rhs.getValue(row, column))
						return false;
				}
			}

			return true;
		}

		bool operator!=(const Vector3<T>& rhs) const
		{
			for (int row = 0; row < 3; row++)
			{
				for (int column = 0; column < 3; column++)
				{
					if (data[row][column] == rhs.getValue(row, column))
						return false;
				}
			}

			return true;
		}

	public:
		T data[3][3];
	};

	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<double> Matrix3d;
}