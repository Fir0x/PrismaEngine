#include "../public/Camera.h"

#include "core/maths/public/utils.h"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace PrismaEngine
{
	Camera::Camera(const Vector3f& position, float yaw, float pitch, float aspectRatio)
	{
		initialize(buildProjection(0.1f, 60.0f, aspectRatio), position, yaw, pitch);
	}

	Camera::Camera(const Vector3f& position, float yaw, float pitch) : Camera(position, yaw, pitch, 16.0f / 9.0f)
	{
	}

	Camera::Camera(const Vector3f& position, float aspectRatio) : Camera(position, 0.0f, 0.0f, aspectRatio)
	{
	}

	Camera::Camera(const Vector3f& position) : Camera(position, 0.0f, 0.0f)
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
		m_yaw = 0.0f;
		m_pitch = 0.0f;
		m_projMatrix = frustum;
		m_transform = Transform(pos);

		rotate(yaw, pitch);
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
		return -m_transform.getForward();
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
		m_transform.translate(-translation);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(Vector3f(x, y, z));
	}

	void Camera::rotate(float deltaYaw, float deltaPitch)
	{
		m_pitch = clamp(m_pitch + deltaPitch, -89.0f, 89.0f);
		m_yaw += deltaYaw;

		while (m_yaw < -360.0f)
			m_yaw += 360.0f;

		while (m_yaw > 360.0f)
			m_yaw -= 360.0f;

		// If yaw and pitch are 0, the camera look at +Z axis
		Vector3f direction;
		float yawCos = cos(degreesToRadians(m_yaw));
		float yawSin = sin(degreesToRadians(m_yaw));
		float pitchCos = cos(degreesToRadians(m_pitch));
		float pitchSin = sin(degreesToRadians(m_pitch));

		direction.x = yawSin * pitchCos;
		direction.y = pitchSin;
		direction.z = yawCos * pitchCos;

		lookAt(position() + direction);

		Vector3f pos = m_transform.getPosition();
		spdlog::info("Transform pos: {} {} {}", pos.x, pos.y, pos.z);
	}

	void Camera::lookAt(const Vector3f& target)
	{
		const Vector3f cameraPosition = -position();
		const Vector3f forward = -(target - cameraPosition).normalize();
		const Vector3f right = forward.cross(Vector3f(0.0f, 1.0f, 0.0f)).normalize();
		const Vector3f up = right.cross(forward);

		Matrix4f transformMatrix(
			right.x, up.x, forward.x, 0.0f,
			right.y, up.y, forward.y, 0.0f,
			right.z, up.z, forward.z, 0.0f,
			-right.dot(cameraPosition), -up.dot(cameraPosition), -forward.dot(cameraPosition), 1.0f
		);

		m_transform.setMatrix(transformMatrix);
	}

	void Camera::getRotation(float& yaw, float& pitch)
	{
		Vector3f camerDirection = forward();

		pitch = asin(camerDirection.y);
		yaw = acos(camerDirection.x / cos(pitch));
	}
}