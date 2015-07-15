#include "FlyInput.h"

#include "GLFW\glfw3.h"

using namespace reng;

void FlyInput::Update(GLFWwindow* pWindow, double deltaTime)
{
	HandleKeyboard(pWindow, deltaTime);
	HandleMouse(pWindow);
}


void FlyInput::HandleKeyboard(GLFWwindow* pWindow, double deltaTime)
{
	glm::vec3 moveDir(0.0f);
	Transform transform = GetTransform();

	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		moveDir -= transform.GetForward();
	}

	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		moveDir += transform.GetForward();
	}

	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		moveDir -= transform.GetRight();
	}

	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		moveDir += transform.GetRight();
	}

	if (glfwGetKey(pWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveDir += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		moveDir -= glm::vec3(0.0f, 1.0f, 0.0f);
	}

	float fLength = glm::length(moveDir);
	if (fLength > 0.01f)
	{
		moveDir = ((float)deltaTime * m_flySpeed) * glm::normalize(moveDir);
		transform.SetPosition(transform.GetPosition() + moveDir);
		SetTransform(transform);
	}
}

void FlyInput::HandleMouse(GLFWwindow* pWindow)
{

}
