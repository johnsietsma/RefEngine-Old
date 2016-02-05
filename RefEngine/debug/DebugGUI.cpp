#include "DebugGUI.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


using namespace reng;


DebugGUI::DebugGUI(GLFWwindow* pWindow) :
	m_pWindow(pWindow)
{
}

void DebugGUI::Init()
{
	ImGui_ImplGlfwGL3_Init(m_pWindow, true);
}

void DebugGUI::DeInit()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

bool DebugGUI::StartEntity(int id, const std::string& name)
{
	char nameBuffer[512];
	sprintf(nameBuffer, "%s - %d", name.c_str(), id);
	bool isOpen = ImGui::TreeNode(nameBuffer);
	if( isOpen ) ImGui::PushID(id);
	return isOpen;
}

void DebugGUI::EndEntity()
{
	ImGui::PopID();
	ImGui::TreePop();
}


void DebugGUI::NewFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void DebugGUI::Draw()
{
	ImGui::Render();
}
