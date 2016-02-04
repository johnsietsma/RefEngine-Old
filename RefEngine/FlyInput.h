#pragma once

#include "Camera.h"

struct GLFWwindow;

namespace reng {

class FlyInput {
public:
	FlyInput( Camera* pCamera, GLFWwindow* pWindow, float flySpeed=5, float rotationSpeed=1 ) :
		m_pCamera(pCamera),
        m_pWindow(pWindow),
        m_flySpeed(flySpeed),
        m_rotationSpeed(rotationSpeed),
		m_rotateButtonClicked(false)
	{}

	void Update(double deltaTime);

private:
	void HandleKeyboard(GLFWwindow* pWindow, double deltaTime);
	void HandleMouse(GLFWwindow* pWindow, double deltaTime);

	Transform GetTransform()  { return m_pCamera->GetTransform(); }
	void SetTransform(const Transform& transform) { m_pCamera->SetTransform(transform); }
	void CalculateRotation(double deltaTime, double xOffset, double yOffset);

	Camera* m_pCamera;
    GLFWwindow* m_pWindow;
	float m_flySpeed ;
	float m_rotationSpeed;
	bool m_rotateButtonClicked;
	float m_cursorX, m_cursorY;
};

}