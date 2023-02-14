#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace BerylEngine
{
	class Camera
	{
	private:
		glm::vec3 m_worldUp;

		float m_pitch = 0;
		float m_yaw = 0;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projMatrix;

		void addPitch(float angle);
		void addYaw(float angle);

		void initialize(glm::mat4 frustum, glm::vec3 position, float yaw,
						float pitch, glm::vec3 worldUp);

		void updateView();

	public:
		Camera(glm::mat4 frustum = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f),
				glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
				float yaw = -90.0f,
				float pitch = 0.0f,
				glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

		Camera(glm::vec3 position,
				float yaw = -90.0f,
				float pitch = 0.0f,
				glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 right() const;
		glm::vec3 up() const;
		glm::vec3 forward() const;
		glm::vec3 position() const;

		glm::mat4 viewMatrix();
		glm::mat4 projectionMatrix() const;

		void translate(const glm::vec3& translation);
		void translate(float x, float y, float z);

		void rotate(float pitchAngle, float yawAngle);

		void onScreenSizeChange(int w, int h);
	};
}