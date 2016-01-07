#pragma once

#include "component/TransformComponent.h"

#include "entity/Component.h"
#include "entity/ComponentHandle.h"

#include "glm/glm.hpp"

#include <memory>

namespace reng {

class LightComponent : public IComponent 
{
public:
    LightComponent(const ComponentHandle<TransformComponent>& trans) :
        LightComponent(trans, glm::vec3(1))
    {}

    LightComponent(const ComponentHandle<TransformComponent>& trans, glm::vec3 lightColor) :
        m_transformComponentHandle(trans),
        m_color(lightColor)
    {}

    const glm::vec3& GetDirection() const { return m_transformComponentHandle.GetComponent().GetTransform().GetForward(); }
    const glm::vec3& GetColor() const { return m_color;  }


protected:
    const ComponentHandle<TransformComponent> m_transformComponentHandle;
    glm::vec3 m_color;

};

}