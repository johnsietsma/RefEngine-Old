#include "FlyInput.h"

#include "GLFW\glfw3.h"
#include "glm\mat4x4.hpp"

using namespace reng;

void FlyInput::Update(GLFWwindow* pWindow, double deltaTime)
{
	HandleKeyboard(pWindow, deltaTime);
	HandleMouse(pWindow, deltaTime);
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
		transform.SetPosition(transform.GetPosition() + moveDir);
		SetTransform(transform);
	}
}

void FlyInput::HandleMouse(GLFWwindow* pWindow, double deltaTime)
{
	if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		int width, height;
		glfwGetFramebufferSize(pWindow, &width, &height);

		if (m_rotateButtonClicked == false)
		{
			m_cursorX = (float)floor(width / 2.0);
			m_cursorY = (float)floor(height / 2.0);

			m_rotateButtonClicked = true;
		}
		else
		{
			double mouseX, mouseY;
			glfwGetCursorPos(pWindow, &mouseX, &mouseY);

			double xOffset = mouseX - m_cursorX;
			double yOffset = mouseY - m_cursorY;

			CalculateRotation(deltaTime, xOffset, yOffset);

		}

		glfwSetCursorPos(pWindow, width / 2, height / 2);
	}
	else
	{
		m_rotateButtonClicked = false;
	}
}


void FlyInput::CalculateRotation(double deltaTime, double xOffset, double yOffset)
{
	Transform transform = GetTransform();
	glm::mat4x4 transformMatrix = transform.GetMartix();

	if (xOffset != 0.0)
	{
		glm::mat4x4 rot = glm::rotate((float)(m_rotationSpeed * deltaTime * -xOffset), glm::vec3(0, 1, 0));
		transformMatrix *= rot;
	}

	if (yOffset != 0.0)
	{
		glm::mat4 rot = glm::rotate((float)(m_rotationSpeed * deltaTime * -yOffset), glm::vec3(1, 0, 0));
		transformMatrix *= rot;
	}

	//Clean up rotation
	glm::mat4 oldTrans = transformMatrix;
	glm::mat4 trans;
	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	//Right
	trans[0] = glm::normalize(glm::vec4(glm::cross(worldUp, oldTrans[2].xyz()), 0));
	//Up
	trans[1] = glm::normalize(glm::vec4(glm::cross(oldTrans[2].xyz(), trans[0].xyz()), 0));
	//Forward
	trans[2] = glm::normalize(oldTrans[2]);

	//Position
	trans[3] = oldTrans[3];

	SetTransform(trans);
}