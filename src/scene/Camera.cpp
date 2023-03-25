#include "Camera.h"

#include <glm/ext.hpp>

namespace BerylEngine
{
	Camera::Camera(const glm::vec3& position, float yaw, float pitch, float aspectRatio)
	{
		initialize(buildProjection(0.1f, 60.0f, aspectRatio), position, yaw, pitch);
	}

	Camera::Camera(const glm::vec3& position, float yaw, float pitch) : Camera(position, yaw, pitch, 16.0f / 9.0f)
	{
	}

	Camera::Camera(const glm::vec3& position, float aspectRatio) : Camera(position, -90.0f, 0.0f, aspectRatio)
	{
	}

	Camera::Camera(const glm::vec3& position) : Camera(position, -90.0f, 0.0f)
	{
	}

	Camera::Camera() : Camera(glm::vec3(0.0f))
	{
	}

	glm::mat4 Camera::buildProjection(float zNear, float fovYDegree, float aspectRatio)
	{
		float fovYRadian = glm::radians(fovYDegree);
		float f = 1.0f / tan(fovYRadian / 2.0f);
		return glm::mat4(
			f / aspectRatio, 0.0f, 0.0f, 0.0f,
			0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, zNear, 0.0f);
	}

	void Camera::initialize(const glm::mat4& frustum, const glm::vec3& pos, float yaw, float pitch)
	{
		m_yaw = yaw;
		m_pitch = pitch;
		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_projMatrix = frustum;

		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward = glm::normalize(forward);

		m_viewMatrix = glm::lookAt(pos, pos + forward, m_worldUp);
	}

	glm::vec3 Camera::right() const
	{
		return glm::row(m_viewMatrix, 0);
	}

	glm::vec3 Camera::up() const
	{
		return glm::row(m_viewMatrix, 1);
	}

	glm::vec3 Camera::forward() const
	{
		return -glm::row(m_viewMatrix, 2);
	}

	glm::mat4 Camera::viewMatrix() const
	{
		return m_viewMatrix;
	}

	glm::mat4 Camera::projectionMatrix() const
	{
		return m_projMatrix;
	}

	glm::vec3 Camera::position() const
	{
		glm::vec3 pos(0.0f);
		for (int i = 0; i < 3; i++)
			pos -= glm::vec3(m_viewMatrix[0][i], m_viewMatrix[1][i], m_viewMatrix[2][i]) * m_viewMatrix[3][i];

		return pos;
	}

	void Camera::updateView()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward = glm::normalize(forward);

		glm::vec3 position = this->position();
		m_viewMatrix = glm::lookAt(position, position + forward, m_worldUp);
	}

	void Camera::translate(const glm::vec3& translation)
	{
		glm::vec3 position = this->position() + translation;
		m_viewMatrix = glm::lookAt(position, position + forward(), m_worldUp);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(glm::vec3(x, y, z));
	}

	void Camera::addPitch(float angle)
	{
		m_pitch += angle;
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		else if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	void Camera::addYaw(float angle)
	{
		m_yaw += angle;
	}

	void Camera::rotate(float pitchAngle, float yawAngle)
	{
		addPitch(pitchAngle);
		addYaw(yawAngle);

		updateView();
	}

	void Camera::onScreenSizeChange(int w, int h)
	{
		m_projMatrix = glm::perspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	}
}