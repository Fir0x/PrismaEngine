#include "GUIRenderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace BerylEngine
{
	GUIRenderer::GUIRenderer(GLFWwindow* window) : m_window(window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450");

		ImGui::StyleColorsDark();
	}

	GUIRenderer::~GUIRenderer()
	{
	}

	void GUIRenderer::start()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUIRenderer::finish()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool GUIRenderer::forwardMouseEvent(int button, bool down) const
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(button == GLFW_MOUSE_BUTTON_LEFT ? ImGuiMouseButton_Left : ImGuiMouseButton_Right, down);

		return !io.WantCaptureMouse;
	}
}