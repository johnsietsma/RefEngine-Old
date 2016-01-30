#pragma once

#include "component/UpdateComponent.h"

#include "entity/Component.h"
#include "entity/ComponentDatabase.h"
#include "entity/ComponentHandle.h"

#include "FlyInput.h"

#include <memory>

class GLFWindow;

namespace reng {

class Camera;

class FlyInputComponent : public UpdateComponent
{
public:
    FlyInputComponent(Camera* pCamera, GLFWwindow* pWindow, float flySpeed, float rotationSpeed) :
        m_flyInput(pCamera, pWindow, flySpeed, rotationSpeed)
    {}

    void Update(double deltaTime, ComponentDatabase& database)
    {
        m_flyInput.Update(deltaTime);
    }

private:
    FlyInput m_flyInput;
};

}