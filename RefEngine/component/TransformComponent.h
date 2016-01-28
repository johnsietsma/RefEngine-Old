#pragma once

#include "Transform.h"

#include "component/DebugComponent.h"

#include "entity/Component.h"

namespace reng {

class TransformComponent : public DebugComponent
{
public:
    TransformComponent()
    {
    }

    TransformComponent(Transform trans) :
        m_transform(trans)
    {}

	const Transform& GetTransform() const { return m_transform; }
	void SetTransform(const Transform& transform) { m_transform = transform; }


protected:
    Transform m_transform;
};

}
