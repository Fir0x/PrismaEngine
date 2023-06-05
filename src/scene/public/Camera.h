#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"

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
		Matrix4f projectionMatrix() const;

		void translate(const Vector3f& translation);
		void translate(float x, float y, float z);

		void rotate(float pitchAngle, float yawAngle);

		void onScreenSizeChange(int w, int h);

	private:
		Vector3f m_worldUp;

		float m_pitch = 0;
		float m_yaw = 0;

		Matrix4f m_viewMatrix;
		Matrix4f m_projMatrix;

		void addPitch(float angle);
		void addYaw(float angle);

		Matrix4f buildProjection(float zNear, float fovYDegree, float aspectRatio);
		void initialize(const Matrix4f& frustum, const Vector3f& position, float yaw,
			float pitch);

		void updateView();
	};
}