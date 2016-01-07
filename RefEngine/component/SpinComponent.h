#pragma once

#include "component/TransformComponent.h"
#include "component/UpdateComponent.h"

#include "entity/ComponentHandle.h"

#include <glm/gtx/transform.hpp>

class SpinComponent : public reng::UpdateComponent {
public:
    SpinComponent(reng::ComponentHandle<reng::TransformComponent>& transComp, float spinSpeed) :
        m_transformComponentHandle(transComp),
        m_spinSpeed(spinSpeed)
    {}

    void Update(double deltaTime) override
    {
        auto& transComponent = m_transformComponentHandle.GetComponent();
        auto trans = transComponent.GetTransform();
        trans = glm::rotate<float>(trans.GetMartix(), (float)(m_spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
        transComponent.SetTransform(trans);
    }

private:
    reng::ComponentHandle<reng::TransformComponent> m_transformComponentHandle;
    float m_spinSpeed;
};
