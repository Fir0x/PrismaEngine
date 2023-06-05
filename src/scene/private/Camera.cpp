#include "../public/Camera.h"

#include <glm/ext.hpp>

#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Camera::Camera(const Vector3f& position, float yaw, float pitch, float aspectRatio)
	{
		initialize(buildProjection(0.1f, 60.0f, aspectRatio), position, yaw, pitch);
	}

	Camera::Camera(const Vector3f& position, float yaw, float pitch) : Camera(position, yaw, pitch, 16.0f / 9.0f)
	{
	}

	Camera::Camera(const Vector3f& position, float aspectRatio) : Camera(position, -90.0f, 0.0f, aspectRatio)
	{
	}

	Camera::Camera(const Vector3f& position) : Camera(position, -90.0f, 0.0f)
	{
	}

	Camera::Camera() : Camera(Vector3f(0.0f))
	{
	}

	Matrix4f Camera::buildProjection(float zNear, float fovYDegree, float aspectRatio)
	{
		float fovYRadian = degreesToRadians(fovYDegree);
		float f = 1.0f / tan(fovYRadian / 2.0f);
		return Matrix4f(
			f / aspectRatio, 0.0f, 0.0f, 0.0f,
			0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, zNear, 0.0f);
	}

	void Camera::initialize(const Matrix4f& frustum, const Vector3f& pos, float yaw, float pitch)
	{
		m_yaw = yaw;
		m_pitch = pitch;
		m_worldUp = Vector3f(0.0f, 1.0f, 0.0f);
		m_projMatrix = frustum;

		Vector3f forward;
		forward.x = cos(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward.y = sin(degreesToRadians(m_pitch));
		forward.z = sin(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward = forward.normalize();

		m_viewMatrix = lookAt(pos, pos + forward, m_worldUp);
	}

	Vector3f Camera::right() const
	{
		return m_viewMatrix.getRow(0);
	}

	Vector3f Camera::up() const
	{
		return m_viewMatrix.getRow(1);
	}

	Vector3f Camera::forward() const
	{
		return -m_viewMatrix.getRow(2);
	}

	Matrix4f Camera::viewMatrix() const
	{
		return m_viewMatrix;
	}

	Matrix4f Camera::projectionMatrix() const
	{
		return m_projMatrix;
	}

	Vector3f Camera::position() const
	{
		Vector3f pos(0.0f);
		for (int i = 0; i < 3; i++)
			pos -= Vector3f(m_viewMatrix.data[0][i], m_viewMatrix.data[1][i], m_viewMatrix.data[2][i]) * m_viewMatrix.data[3][i];

		return pos;
	}

	void Camera::updateView()
	{
		Vector3f forward;
		forward.x = cos(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward.y = sin(degreesToRadians(m_pitch));
		forward.z = sin(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward = forward.normalize();

		Vector3f position = this->position();
		m_viewMatrix = lookAt(position, position + forward, m_worldUp);
	}

	void Camera::translate(const Vector3f& translation)
	{
		Vector3f position = this->position() + translation;
		m_viewMatrix = lookAt(position, position + forward(), m_worldUp);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(Vector3f(x, y, z));
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
		m_projMatrix = perspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	}
}