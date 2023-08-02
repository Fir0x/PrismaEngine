#pragma once

#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "Transform.h"

namespace PrismaEngine
{
	class Camera
	{
	public:
		Camera(const Vector3f& position, float yaw, float pitch, float aspectRatio);
		Camera(const Vector3f& position, float yaw, float pitch);
		Camera(const Vector3f& position, float aspectRatio);
		Camera(const Vector3f& position);
		Camera();

		Vector3f right() const;
		Vector3f up() const;
		Vector3f forward() const;
		Vector3f position() const;

		Matrix4f viewMatrix() const;
		const Matrix4f& projectionMatrix() const;

		void translate(const Vector3f& translation);
		void translate(float x, float y, float z);

		void rotate(float deltaYaw, float deltaPitch);
		void lookAt(const Vector3f& target);
		void getRotation(float& yaw, float& pitch);

	private:
		Matrix4f buildProjection(float zNear, float fovYDegree, float aspectRatio);
		void initialize(const Matrix4f& frustum, const Vector3f& position, float yaw,
			float pitch);

	private:
		float m_yaw;
		float m_pitch;
		Transform m_transform;
		Matrix4f m_projMatrix;
	};
}