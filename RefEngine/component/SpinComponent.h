#pragma once

#include "component/TransformComponent.h"
#include "component/UpdateComponent.h"

#include "entity/ComponentHandle.h"

#include <glm/gtx/transform.hpp>

namespace reng {

class SpinComponent : public UpdateComponent {
public:
    SpinComponent(reng::ComponentHandle transComponentHandle, float spinSpeed) :
        m_transformComponentHandle(transComponentHandle),
        m_spinSpeed(spinSpeed)
    {}

    void Update(double deltaTime, ComponentDatabase& database) override
    {
        auto& transComponent = database.GetComponent<TransformComponent>( m_transformComponentHandle );
        auto trans = transComponent.GetTransform();
		glm::quat rot = glm::angleAxis((float)(m_spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
		trans.Rotate(rot);
        transComponent.SetTransform(trans);
    }

private:
    reng::ComponentHandle m_transformComponentHandle;
    float m_spinSpeed;
};

}