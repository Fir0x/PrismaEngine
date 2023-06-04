#pragma once

#include "Vector4.h"

namespace PrismaEngine
{
	template<typename T>
	class Matrix4
	{
	public:
		Matrix4() = default;

		Matrix4(const T& x)
		{
			data[0][0] = x;
			data[0][1] = static_cast<T>(0);
			data[0][2] = static_cast<T>(0);
			data[0][3] = static_cast<T>(0);

			data[1][0] = static_cast<T>(0);
			data[1][1] = x;
			data[1][2] = static_cast<T>(0);
			data[1][3] = static_cast<T>(0);

			data[2][0] = static_cast<T>(0);
			data[2][1] = static_cast<T>(0);
			data[2][2] = x;
			data[2][3] = static_cast<T>(0);

			data[3][0] = static_cast<T>(0);
			data[3][1] = static_cast<T>(0);
			data[3][2] = static_cast<T>(0);
			data[3][3] = x;
		}

		Matrix4(const Vector4<T>& row0, const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3)
		{
			data[0][0] = row0.x;
			data[0][1] = row0.y;
			data[0][2] = row0.z;
			data[0][3] = row0.w;

			data[1][0] = row1.x;
			data[1][1] = row1.y;
			data[1][2] = row1.z;
			data[1][3] = row1.w;

			data[2][0] = row2.x;
			data[2][1] = row2.y;
			data[2][2] = row2.z;
			data[2][3] = row2.w;

			data[3][0] = row3.x;
			data[3][1] = row3.y;
			data[3][2] = row3.z;
			data[3][3] = row3.w;
		}

		static Matrix4<T> fromPlane(const Vector4<T>& xPlane, const Vector4<T>& yPlane,
									const Vector4<T>& zPlane, const Vector4<T>& wPlane)
		{
			Matrix4<T> result;

			result.data[0][0] = xPlane.x;
			result.data[0][1] = yPlane.x;
			result.data[0][2] = zPlane.x;
			result.data[0][3] = wPlane.x;

			result.data[1][0] = xPlane.y;
			result.data[1][1] = yPlane.y;
			result.data[1][2] = zPlane.y;
			result.data[1][3] = wPlane.y;

			result.data[2][0] = xPlane.z;
			result.data[2][1] = yPlane.z;
			result.data[2][2] = zPlane.z;
			result.data[2][3] = wPlane.z;

			result.data[3][0] = xPlane.w;
			result.data[3][1] = yPlane.w;
			result.data[3][2] = zPlane.w;
			result.data[3][3] = wPlane.w;

			return result;
		}

		static Matrix4<T> identity()
		{
			return Matrix4<T>(static_cast<T>(1));
		}

		T determinant() const
		{
			const float subSubFactor01 = data[0][2] * data[1][3] - data[1][2] * data[0][3];
			const float subSubFactor12 = data[1][2] * data[2][3] - data[2][2] * data[1][3];
			const float subSubFactor23 = data[2][2] * data[3][3] - data[3][2] * data[2][3];
			const float subSubFactor02 = data[0][2] * data[2][3] - data[2][2] * data[0][3];
			const float subSubFactor13 = data[1][2] * data[3][3] - data[3][2] * data[1][3];
			const float subSubFactor03 = data[0][2] * data[3][3] - data[3][2] * data[0][3];

			const float subFactor0 = data[1][1] * subSubFactor23 - data[2][1] * subSubFactor13 + data[3][1] * subSubFactor12;
			const float subFactor1 = data[0][1] * subSubFactor23 - data[2][1] * subSubFactor03 + data[3][1] * subSubFactor02;
			const float subFactor2 = data[0][1] * subSubFactor13 - data[1][1] * subSubFactor03 + data[3][1] * subSubFactor01;
			const float subFactor3 = data[0][1] * subSubFactor12 - data[1][1] * subSubFactor02 + data[2][1] * subSubFactor01;

			return data[0][0] * subFactor0 - data[1][0] * subFactor1 + data[2][0] * subFactor2 - data[3][0] * subFactor3;
		}

		Matrix4<T> transpose() const
		{
			Vector4<T> x(data[0][0], data[0][1], data[0][2], data[0][3]);
			Vector4<T> y(data[1][0], data[1][1], data[1][2], data[1][3]);
			Vector4<T> z(data[2][0], data[2][1], data[2][2], data[2][3]);
			Vector4<T> w(data[3][0], data[3][1], data[3][2], data[3][3]);

			return fromPlane(x, y, z, w);
		}

		Matrix4<T> inverse() const
		{
			const float coef01 = data[2][1] * data[3][2] - data[2][2] * data[3][1];
			const float coef02 = data[2][1] * data[3][3] - data[2][3] * data[3][1];
			const float coef03 = data[2][2] * data[3][3] - data[2][3] * data[3][2];
			const float coef04 = data[2][0] * data[3][2] - data[2][2] * data[3][0];
			const float coef05 = data[2][0] * data[3][3] - data[2][3] * data[3][0];
			const float coef06 = data[2][0] * data[3][1] - data[2][1] * data[3][0];

			const float coef21 = data[1][1] * data[3][2] - data[1][2] * data[3][1];
			const float coef22 = data[1][1] * data[3][3] - data[1][3] * data[3][1];
			const float coef23 = data[1][2] * data[3][3] - data[1][3] * data[3][2];
			const float coef24 = data[1][0] * data[3][2] - data[1][2] * data[3][0];
			const float coef25 = data[1][0] * data[3][3] - data[1][3] * data[3][0];
			const float coef26 = data[1][0] * data[3][1] - data[1][1] * data[3][0];

			const float coef31 = data[1][1] * data[2][2] - data[1][2] * data[2][1];
			const float coef32 = data[1][1] * data[2][3] - data[1][3] * data[2][1];
			const float coef33 = data[1][2] * data[2][3] - data[1][3] * data[2][2];
			const float coef34 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
			const float coef35 = data[1][0] * data[2][3] - data[1][3] * data[2][0];
			const float coef36 = data[1][0] * data[2][1] - data[1][1] * data[2][0];

			const float adjugateX0 = +(data[1][1] * coef03 - data[1][2] * coef02 + data[1][3] * coef01);
			const float adjugateX1 = -(data[1][0] * coef03 - data[1][2] * coef05 + data[1][3] * coef04);
			const float adjugateX2 = +(data[1][0] * coef02 - data[1][1] * coef05 + data[1][3] * coef06);
			const float adjugateX3 = -(data[1][0] * coef01 - data[1][1] * coef04 + data[1][2] * coef06);

			const float adjugateY0 = -(data[0][1] * coef03 - data[0][2] * coef02 + data[0][3] * coef01);
			const float adjugateY1 = +(data[0][0] * coef03 - data[0][2] * coef05 + data[0][3] * coef04);
			const float adjugateY2 = -(data[0][0] * coef02 - data[0][1] * coef05 + data[0][3] * coef06);
			const float adjugateY3 = +(data[0][0] * coef01 - data[0][1] * coef04 + data[0][2] * coef06);

			const float adjugateZ0 = +(data[0][1] * coef23 - data[0][2] * coef22 + data[0][3] * coef21);
			const float adjugateZ1 = -(data[0][0] * coef23 - data[0][2] * coef25 + data[0][3] * coef24);
			const float adjugateZ2 = +(data[0][0] * coef22 - data[0][1] * coef25 + data[0][3] * coef26);
			const float adjugateZ3 = -(data[0][0] * coef21 - data[0][1] * coef24 + data[0][2] * coef26);

			const float adjugateW0 = -(data[0][1] * coef33 - data[0][2] * coef32 + data[0][3] * coef31);
			const float adjugateW1 = +(data[0][0] * coef33 - data[0][2] * coef35 + data[0][3] * coef34);
			const float adjugateW2 = -(data[0][0] * coef32 - data[0][1] * coef35 + data[0][3] * coef36);
			const float adjugateW3 = +(data[0][0] * coef31 - data[0][1] * coef34 + data[0][2] * coef36);

			const float determinant = data[0][0] * adjugateX0 + data[0][1] * adjugateX1 + data[0][2] * adjugateX2 + data[0][3] * adjugateX3;
			T oneOverDeterminant = static_cast<T>(1) / determinant;

			Vector4<T> inverseX = oneOverDeterminant * Vector4<T>(adjugateX0, adjugateX1, adjugateX2, adjugateX3);
			Vector4<T> inverseY = oneOverDeterminant * Vector4<T>(adjugateY0, adjugateY1, adjugateY2, adjugateY3);
			Vector4<T> inverseZ = oneOverDeterminant * Vector4<T>(adjugateZ0, adjugateZ1, adjugateZ2, adjugateZ3);
			Vector4<T> inverseW = oneOverDeterminant * Vector4<T>(adjugateW0, adjugateW1, adjugateW2, adjugateW3);

			return fromPlane(inverseX, inverseY, inverseZ, inverseW);
		}

		Vector4<T> getColumn(int index) const
		{
			return Vector4<T>(data[0][index], data[1][index], data[2][index], data[3][index]);
		}

		Vector4<T> getRow(int index) const
		{
			const T* row = data[index];
			return Vector4<T>(row[0], row[1], row[2], row[3]);
		}

		const T& getValue(int row, int column) const
		{
			return data[row][column];
		}

		void setValue(int row, int column, T value)
		{
			data[row][column] = value;
		}

		Matrix4<T> operator+(const Matrix4<T>& rhs) const
		{
			Vector4<T> row0 = getRow(0) + rhs.getRow(0);
			Vector4<T> row1 = getRow(1) + rhs.getRow(1);
			Vector4<T> row2 = getRow(2) + rhs.getRow(2);
			Vector4<T> row3 = getRow(3) + rhs.getRow(3);

			return Matrix4<T>(row0, row1, row2, row3);
		}

		Matrix4<T> operator-(const Matrix4<T>& rhs) const
		{
			Vector4<T> row0 = getRow(0) - rhs.getRow(0);
			Vector4<T> row1 = getRow(1) - rhs.getRow(1);
			Vector4<T> row2 = getRow(2) - rhs.getRow(2);
			Vector4<T> row3 = getRow(3) - rhs.getRow(3);

			return Matrix4<T>(row0, row1, row2, row3);
		}

		Matrix4<T> operator*(const Matrix4<T>& rhs) const
		{
			Vector4<T> row0 = Vector4<T>(data[0][0]) * rhs.getRow(0);
			row0 += Vector4<T>(data[0][1]) * rhs.getRow(1);
			row0 += Vector4<T>(data[0][2]) * rhs.getRow(2);
			row0 += Vector4<T>(data[0][3]) * rhs.getRow(3);

			Vector4<T> row1 = Vector4<T>(data[1][0]) * rhs.getRow(0);
			row1 += Vector4<T>(data[1][1]) * rhs.getRow(1);
			row1 += Vector4<T>(data[1][2]) * rhs.getRow(2);
			row1 += Vector4<T>(data[1][3]) * rhs.getRow(3);

			Vector4<T> row2 = Vector4<T>(data[2][0]) * rhs.getRow(0);
			row2 += Vector4<T>(data[2][1]) * rhs.getRow(1);
			row2 += Vector4<T>(data[2][2]) * rhs.getRow(2);
			row2 += Vector4<T>(data[2][3]) * rhs.getRow(3);

			Vector4<T> row3 = Vector4<T>(data[3][0]) * rhs.getRow(0);
			row3 += Vector4<T>(data[3][1]) * rhs.getRow(1);
			row3 += Vector4<T>(data[3][2]) * rhs.getRow(2);
			row3 += Vector4<T>(data[3][3]) * rhs.getRow(3);

			return Matrix4<T>(row0, row1, row2, row3);
		}

		Vector4<T> operator*(const Vector4<T>& rhs) const
		{
			T x = getRow(0).dot(rhs);
			T y = getRow(1).dot(rhs);
			T z = getRow(2).dot(rhs);
			T w = getRow(3).dot(rhs);

			return Vector4<T>(x, y, z, w);
		}

		bool operator==(const Matrix4<T>& rhs) const
		{
			for (int row = 0; row < 4; row++)
			{
				for (int column = 0; column < 4; column++)
				{
					if (data[row][column] != rhs.getValue(row, column))
						return false;
				}
			}

			return true;
		}

		bool operator!=(const Vector4<T>& rhs) const
		{
			for (int row = 0; row < 4; row++)
			{
				for (int column = 0; column < 4; column++)
				{
					if (data[row][column] == rhs.getValue(row, column))
						return false;
				}
			}

			return true;
		}

	public:
		T data[4][4];
	};

	typedef Matrix4<float> Matrix4f;
	typedef Matrix4<double> Matrix4d;
}