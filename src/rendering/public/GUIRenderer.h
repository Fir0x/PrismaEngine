#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace PrismaEngine
{
	class GUIRenderer
	{
	public:
		GUIRenderer(GLFWwindow* window);
		~GUIRenderer();

		void start();
		void finish();

		bool forwardMouseEvent(int button, bool down) const;

	private:
		GLFWwindow* m_window = nullptr;
	};
}