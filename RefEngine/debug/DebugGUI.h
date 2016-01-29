#pragma once

#include <string>

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

	bool StartEntity( const std::string& name );
	void EndEntity();

	void Draw();

private:
	GLFWwindow* m_pWindow;
};

}
