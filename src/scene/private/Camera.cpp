#include "../public/Camera.h"

#include <glm/ext.hpp>

#include "core/maths/public/matrix.h"
#include "core/maths/public/vector.h"
#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Camera::Camera(const Vec3f& position, float yaw, float pitch, float aspectRatio)
	{
		initialize(buildProjection(0.1f, 60.0f, aspectRatio), position, yaw, pitch);
	}

	Camera::Camera(const Vec3f& position, float yaw, float pitch) : Camera(position, yaw, pitch, 16.0f / 9.0f)
	{
	}

	Camera::Camera(const Vec3f& position, float aspectRatio) : Camera(position, -90.0f, 0.0f, aspectRatio)
	{
	}

	Camera::Camera(const Vec3f& position) : Camera(position, -90.0f, 0.0f)
	{
	}

	Camera::Camera() : Camera(Vec3f(0.0f))
	{
	}

	Mat4f Camera::buildProjection(float zNear, float fovYDegree, float aspectRatio)
	{
		float fovYRadian = degreesToRadians(fovYDegree);
		float f = 1.0f / tan(fovYRadian / 2.0f);
		return Mat4f(
			f / aspectRatio, 0.0f, 0.0f, 0.0f,
			0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, zNear, 0.0f);
	}

	void Camera::initialize(const Mat4f& frustum, const Vec3f& pos, float yaw, float pitch)
	{
		m_yaw = yaw;
		m_pitch = pitch;
		m_worldUp = Vec3f(0.0f, 1.0f, 0.0f);
		m_projMatrix = frustum;

		Vec3f forward;
		forward.x = cos(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward.y = sin(degreesToRadians(m_pitch));
		forward.z = sin(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward = normalize(forward);

		m_viewMatrix = lookAt(pos, pos + forward, m_worldUp);
	}

	Vec3f Camera::right() const
	{
		return row(m_viewMatrix, 0);
	}

	Vec3f Camera::up() const
	{
		return row(m_viewMatrix, 1);
	}

	Vec3f Camera::forward() const
	{
		return -row(m_viewMatrix, 2);
	}

	Mat4f Camera::viewMatrix() const
	{
		return m_viewMatrix;
	}

	Mat4f Camera::projectionMatrix() const
	{
		return m_projMatrix;
	}

	Vec3f Camera::position() const
	{
		Vec3f pos(0.0f);
		for (int i = 0; i < 3; i++)
			pos -= Vec3f(m_viewMatrix[0][i], m_viewMatrix[1][i], m_viewMatrix[2][i]) * m_viewMatrix[3][i];

		return pos;
	}

	void Camera::updateView()
	{
		Vec3f forward;
		forward.x = cos(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward.y = sin(degreesToRadians(m_pitch));
		forward.z = sin(degreesToRadians(m_yaw)) * cos(degreesToRadians(m_pitch));
		forward = normalize(forward);

		Vec3f position = this->position();
		m_viewMatrix = lookAt(position, position + forward, m_worldUp);
	}

	void Camera::translate(const Vec3f& translation)
	{
		Vec3f position = this->position() + translation;
		m_viewMatrix = lookAt(position, position + forward(), m_worldUp);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(Vec3f(x, y, z));
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