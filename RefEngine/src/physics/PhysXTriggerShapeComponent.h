#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"


namespace physx
{
	class PxRigidActor;
	class PxShape;
	class PxScene;
}

namespace reng {

struct PhysXTriggerShapeComponent
{
	PhysXTriggerShapeComponent( physx::PxScene* pScene, physx::PxRigidActor* pActor);

	bool isTriggered;
	physx::PxShape* pShape;
};

class PhysXTriggerShapeProcessor : public reng::Processor<PhysXTriggerShapeComponent>
{
	void CreateShape(physx::PxRigidActor* pActor);

	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager) override;

};

}