#pragma once

#include "Camera.h"

struct GLFWwindow;

namespace reng {

class FlyInput {
public:
	FlyInput( Camera* pCamera ) :
		m_pCamera(pCamera),
		m_rotateButtonClicked(false)
	{}

	void Update(GLFWwindow* pWindow, double deltaTime);

private:
	void HandleKeyboard(GLFWwindow* pWindow, double deltaTime);
	void HandleMouse(GLFWwindow* pWindow, double deltaTime);

	Transform GetTransform()  { return m_pCamera->GetTransform(); }
	void SetTransform(const Transform& transform) { m_pCamera->SetTransform(transform); }
	void CalculateRotation(double deltaTime, double xOffset, double yOffset);

	Camera* m_pCamera;
	float m_flySpeed = 5;
	float m_rotationSpeed = 1;
	bool m_rotateButtonClicked;
	float m_cursorX, m_cursorY;
};

}