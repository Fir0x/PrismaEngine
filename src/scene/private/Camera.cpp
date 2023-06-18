#include "../public/Camera.h"

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
			0.0f, 0.0f, 0.0f, zNear,
			0.0f, 0.0f, -1.0f , 0.0f);
	}

	void Camera::initialize(const Matrix4f& frustum, const Vector3f& pos, float yaw, float pitch)
	{
		m_yaw = yaw;
		m_pitch = pitch;
		m_worldUp = Vector3f(0.0f, 1.0f, 0.0f);
		m_projMatrix = frustum;
	}

	Vector3f Camera::right() const
	{
		return m_transform.getRight();
	}

	Vector3f Camera::up() const
	{
		return m_transform.getUp();
	}

	Vector3f Camera::forward() const
	{
		return m_transform.getForward();
	}

	const Matrix4f& Camera::viewMatrix() const
	{
		return m_transform.getMatrix();
	}

	const Matrix4f& Camera::projectionMatrix() const
	{
		return m_projMatrix;
	}

	Vector3f Camera::position() const
	{
		return m_transform.getPosition();
	}

	void Camera::translate(const Vector3f& translation)
	{
		m_transform.translate(translation);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(Vector3f(x, y, z));
	}

	void Camera::rotate(float pitchAngle, float yawAngle)
	{
		m_pitch = clamp(m_pitch + pitchAngle, -89.0f, 89.0f);
		m_yaw += yawAngle;

		m_transform.setRotation(m_pitch, m_yaw, 0.0f);
	}
}