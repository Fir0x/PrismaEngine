#pragma once

#include <glm/glm.hpp>

namespace BerylEngine
{
	class Transform
	{
	public:
		Transform();
		Transform(const glm::vec3& position);

		void translate(const glm::vec3& translation);
		void rotate(float angleX, float angleY, float angleZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		/**
		 * @brief Uniform scaling on all axes
		 * @param factor 
		*/
		void scale(float factor);

		const glm::mat4& getMatrix() const;
		const glm::vec3 getRight() const;
		const glm::vec3 getUp() const;
		const glm::vec3 getForward() const;

	private:
		glm::mat4 m_transforms;
	};
}