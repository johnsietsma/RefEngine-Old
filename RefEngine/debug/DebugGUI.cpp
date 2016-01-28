#include "DebugGUI.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


using namespace reng;


void DebugGUI::Init(GLFWwindow* pWindow, ComponentDatabase* pComponentDatabase)
{
	ImGui_ImplGlfwGL3_Init(pWindow, true);
}

void DebugGUI::DeInit()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

void DebugGUI::Draw()
{
	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Render();
}
