#pragma once

#include "component/TransformComponent.h"

#include "entity/ComponentHandle.h"

#include "glm/glm.hpp"

#include <memory>

namespace reng {

class LightComponent 
{
public:
    LightComponent(const ComponentHandle& transComponentHandle) :
        LightComponent(transComponentHandle, glm::vec3(1))
    {}

    LightComponent(const ComponentHandle& transComponentHandle, glm::vec3 lightColor) :
        m_transformComponentHandle(transComponentHandle),
        m_color(lightColor)
    {}

	ComponentHandle GetTransformComponentHandle() const { return m_transformComponentHandle;  }
    glm::vec3 GetColor() const { return m_color;  }

protected:
    const ComponentHandle m_transformComponentHandle;
    glm::vec3 m_color;

};

}