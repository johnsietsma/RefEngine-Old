#pragma once

#include "Camera.h"

struct GLFWwindow;

namespace reng {

class FlyInput {
public:
	FlyInput( Camera* pCamera ) :
		m_pCamera(pCamera)
	{}

	void Update(GLFWwindow* pWindow, double deltaTime);

private:
	void HandleKeyboard(GLFWwindow* pWindow, double deltaTime);
	void HandleMouse(GLFWwindow* pWindow);

	Transform GetTransform()  { return m_pCamera->GetTransform(); }
	void SetTransform(const Transform& transform) { m_pCamera->SetTransform(transform); }

	Camera* m_pCamera;
	float m_flySpeed = 1;
};

}