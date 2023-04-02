#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../scene/Camera.h"
#include "../rendering/GUIRenderer.h"

namespace BerylEngine
{
	void linkCamera(BerylEngine::Camera* camera);
	void processInput(GLFWwindow* window, const GUIRenderer& guiRenderer);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
}