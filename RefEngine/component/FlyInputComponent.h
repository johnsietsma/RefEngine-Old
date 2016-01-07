#pragma once

#include "component/UpdateComponent.h"

#include "entity/Component.h"
#include "entity/ComponentHandle.h"

#include "FlyInput.h"

#include <memory>

class GLFWindow;

namespace reng {

class Camera;

class FlyInputComponent : public UpdateComponent
{
public:
    FlyInputComponent(Camera* pCamera, GLFWwindow* pWindow) :
        m_flyInput(pCamera, pWindow)
    {}

    void Update(double deltaTime)
    {
        m_flyInput.Update(deltaTime);
    }

private:
    FlyInput m_flyInput;
};

}