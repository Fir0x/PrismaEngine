#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/maths/public/vec3f.h"

namespace PrismaEngine
{
	class Camera
	{
	public:
		Camera(const Vec3f& position, float yaw, float pitch, float aspectRatio);
		Camera(const Vec3f& position, float yaw, float pitch);
		Camera(const Vec3f& position, float aspectRatio);
		Camera(const Vec3f& position);
		Camera();

		Vec3f right() const;
		Vec3f up() const;
		Vec3f forward() const;
		Vec3f position() const;

		glm::mat4 viewMatrix() const;
		glm::mat4 projectionMatrix() const;

		void translate(const Vec3f& translation);
		void translate(float x, float y, float z);

		void rotate(float pitchAngle, float yawAngle);

		void onScreenSizeChange(int w, int h);

	private:
		Vec3f m_worldUp;

		float m_pitch = 0;
		float m_yaw = 0;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projMatrix;

		void addPitch(float angle);
		void addYaw(float angle);

		glm::mat4 buildProjection(float zNear, float fovYDegree, float aspectRatio);
		void initialize(const glm::mat4& frustum, const Vec3f& position, float yaw,
			float pitch);

		void updateView();
	};
}