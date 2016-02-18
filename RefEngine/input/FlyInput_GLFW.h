#pragma once

#include "Camera.h"

#include "glm/fwd.hpp"

struct GLFWwindow;

namespace reng {

class FlyInput {
public:
	FlyInput( GLFWwindow* pWindow, float flySpeed=5, float rotationSpeed=1 ) :
        m_pWindow(pWindow),
        m_flySpeed(flySpeed),
        m_rotationSpeed(rotationSpeed),
		m_rotateButtonClicked(false)
	{}

	Transform UpdateTransform(const Transform& transform, double deltaTime);

private:
	void HandleKeyboard(Transform& transform, GLFWwindow* pWindow, double deltaTime);
	void HandleMouse(Transform& transform, GLFWwindow* pWindow, double deltaTime);

	glm::quat CalculateRotation(glm::vec3 up, glm::vec3 right, double deltaTime, double xOffset, double yOffset);
	
    GLFWwindow* m_pWindow;
	float m_flySpeed ;
	float m_rotationSpeed;
	bool m_rotateButtonClicked;
	float m_cursorX, m_cursorY;
};

}