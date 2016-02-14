#pragma once

#include "component/CameraComponent.h"
#include "component/UpdateComponent.h"

#include "entity/Component.h"
#include "entity/ComponentDatabase.h"
#include "entity/ComponentHandle.h"

#include "input/FlyInput_GLFW.h"

#include <memory>

class GLFWindow;

namespace reng {

class Camera;

class FlyInputComponent : public UpdateComponent
{
public:
    FlyInputComponent(ComponentHandle transformComponentHandle, GLFWwindow* pWindow, float flySpeed, float rotationSpeed) :
		m_transformComponentHandle(transformComponentHandle),
        m_flyInput(pWindow, flySpeed, rotationSpeed)
    {
	}

    void Update(double deltaTime, ComponentDatabase& database)
    {
		auto& transformComponent = database.GetComponent<TransformComponent>(m_transformComponentHandle);
        Transform newTransform = m_flyInput.UpdateTransform(transformComponent.GetTransform(), deltaTime);
		transformComponent.SetTransform(newTransform);
    }

private:
	ComponentHandle m_transformComponentHandle;
    FlyInput m_flyInput;
};

}