#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace BerylEngine
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, float yaw, float pitch, float aspectRatio);
		Camera(const glm::vec3& position, float yaw, float pitch);
		Camera(const glm::vec3& position, float aspectRatio);
		Camera(const glm::vec3& position);
		Camera();

		glm::vec3 right() const;
		glm::vec3 up() const;
		glm::vec3 forward() const;
		glm::vec3 position() const;

		glm::mat4 viewMatrix() const;
		glm::mat4 projectionMatrix() const;

		void translate(const glm::vec3& translation);
		void translate(float x, float y, float z);

		void rotate(float pitchAngle, float yawAngle);

		void onScreenSizeChange(int w, int h);

	private:
		glm::vec3 m_worldUp;

		float m_pitch = 0;
		float m_yaw = 0;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projMatrix;

		void addPitch(float angle);
		void addYaw(float angle);

		glm::mat4 buildProjection(float zNear, float fovYDegree, float aspectRatio);
		void initialize(const glm::mat4& frustum, const glm::vec3& position, float yaw,
			float pitch);

		void updateView();
	};
}