#include "input/FlyInput_GLFW.h"

#include "GLFW/glfw3.h"

#include "glm/gtx/transform.hpp"
#include "glm/mat4x4.hpp"


using namespace reng;



Transform FlyInput::UpdateTransform(const Transform& transform, double deltaTime)
{
	Transform newTransform = transform;
	HandleKeyboard(newTransform, m_pWindow, deltaTime);
	HandleMouse(newTransform, m_pWindow, deltaTime);
	return newTransform;
}


void FlyInput::HandleKeyboard(Transform& transform, GLFWwindow* pWindow, double deltaTime)
{
	glm::vec3 moveDir(0.0f);

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
		//moveDir += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		//moveDir -= glm::vec3(0.0f, 1.0f, 0.0f);
	}

	float fLength = glm::length(moveDir);
	if (fLength > 0.01f)
	{
		moveDir = ((float)deltaTime * m_flySpeed) * glm::normalize(moveDir);
		transform.Translate(moveDir);
	}
}

void FlyInput::HandleMouse(Transform& transform, GLFWwindow* pWindow, double deltaTime)
{
	if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		int width, height;
		glfwGetFramebufferSize(pWindow, &width, &height);
        
        double mouseX, mouseY;
        glfwGetCursorPos(pWindow, &mouseX, &mouseY);

		if (m_rotateButtonClicked == false)
		{
			m_cursorX = (float)mouseX;
			m_cursorY = (float)mouseY;

			m_rotateButtonClicked = true;
		}
		else
		{
			double xOffset = mouseX - m_cursorX;
			double yOffset = mouseY - m_cursorY;

			m_cursorX = (float)mouseX;
			m_cursorY = (float)mouseY;

			glm::quat rot = CalculateRotation(glm::vec3(0, 1, 0), transform.GetRight(), deltaTime, xOffset, yOffset);
			transform.Rotate(rot);
		}

//		glfwSetCursorPos(pWindow, width / 2, height / 2);
	}
	else
	{
		m_rotateButtonClicked = false;
	}
}


glm::quat FlyInput::CalculateRotation(glm::vec3 up, glm::vec3 right, double deltaTime, double xOffset, double yOffset)
{
	glm::quat vertRot, horzRot;
	if (xOffset != 0.0)
	{
		vertRot = glm::angleAxis((float)(-xOffset * m_rotationSpeed * deltaTime), up);
	}

	if (yOffset != 0.0)
	{
		horzRot = glm::angleAxis((float)(-yOffset * m_rotationSpeed * deltaTime), right);
	}

	return horzRot * vertRot;
}
