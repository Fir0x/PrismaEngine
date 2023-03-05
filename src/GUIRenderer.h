#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace BerylEngine
{
	class GUIRenderer
	{
	private:
		GLFWwindow* m_window = nullptr;

	public:
		GUIRenderer(GLFWwindow* window);
		~GUIRenderer();

		void start();
		void finish();

		bool forwardMouseEvent(int button, bool down) const;
	};
}