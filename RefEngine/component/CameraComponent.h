#pragma once

#include "component/TransformComponent.h"
#include "component/UpdateComponent.h"

#include "entity/ComponentHandle.h"

#include <memory>

namespace reng {

class Camera;

class CameraComponent : UpdateComponent
{
public:
    CameraComponent(ComponentHandle transformCompnentHandle, std::shared_ptr<Camera> pCamera) :
		m_transformComponentHandle(transformCompnentHandle),
		m_pCamera( pCamera )
    {
	}

    Camera* GetCamera() { return m_pCamera.get();  }

	void Update(double deltaTime, ComponentDatabase& database) override
	{
		auto& transformComponent = database.GetComponent<TransformComponent>(m_transformComponentHandle);
		m_pCamera->SetTransform(transformComponent.GetTransform());
	}


protected:
	ComponentHandle m_transformComponentHandle;
    std::shared_ptr<Camera> m_pCamera;
};

}