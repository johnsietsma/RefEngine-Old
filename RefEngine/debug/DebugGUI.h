#pragma once

struct GLFWwindow;

namespace reng 
{

class DebugGUI
{
public:
	DebugGUI(GLFWwindow* pWindow);
	DebugGUI() = default;

    void Init();
    void DeInit();

	void NewFrame();
	void Draw();

private:
	GLFWwindow* m_pWindow;
};

}
