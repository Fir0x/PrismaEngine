#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "scene/public/Camera.h"
#include "rendering/public/GUIRenderer.h"

namespace PrismaEngine
{
	void linkCamera(PrismaEngine::Camera* camera);
	void processInput(GLFWwindow* window, const GUIRenderer& guiRenderer);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
}