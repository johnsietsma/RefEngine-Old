#pragma once

struct GLFWwindow;

namespace reng 
{

class ComponentDatabase;

class DebugGUI
{
public:
    void Init(GLFWwindow* pWindow, ComponentDatabase* pComponentDatabase);
    void DeInit();

    void Draw();

	/*template<typename T>
	static void AddDebugVars(TwBar* pBar, T& component) {}

	template<>
	static void AddDebugVars<DebugComponent>(TwBar* pBar, DebugComponent& debugComponent)
	{
		debugComponent.AddDebugVars(pBar);
	}*/

private:
};

}
