
#include "GameTime.h"
#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "physics/PhysXComponent.h"
#include "physics/PhysXTriggerShapeComponent.h"

#include <PxPhysicsAPI.h>


using namespace reng;
using namespace physx;


class TriggerShapeCallback : public PxSimulationEventCallback
{
public:
	TriggerShapeCallback(PhysXTriggerShapeComponent* triggerComponent) :
		m_pTriggerComponent(triggerComponent)
	{

	}

	PhysXTriggerShapeComponent* m_pTriggerComponent;

private:
	void onTrigger(PxTriggerPair* pairs, PxU32 count) override
	{
		for (PxU32 i = 0; i < count; i++)
		{
			// ignore pairs when shapes have been deleted
			if (pairs[i].flags & (PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::eDELETED_SHAPE_OTHER))
				continue;

			m_pTriggerComponent->isTriggered = true;
		}
	}

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {}
	void onWake(PxActor** actors, PxU32 count) override {}
	void onSleep(PxActor** actors, PxU32 count) override {}
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override {}
};


PhysXTriggerShapeComponent::PhysXTriggerShapeComponent(PxScene* pScene, PxRigidActor* pActor):
	isTriggered(false)
{
	pScene->setSimulationEventCallback(new TriggerShapeCallback(this));

	pActor->getShapes(&pShape, 1);
	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

}


void PhysXTriggerShapeProcessor::CreateShape(physx::PxRigidActor* pActor) {
	PxShape* pShape;
	pActor->getShapes(&pShape, 1);
	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
}


void PhysXTriggerShapeProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager)
{
	auto triggerShapeContainer = componentManager.GetComponentContainer<PhysXTriggerShapeComponent>();
	auto physicsContainer = componentManager.GetComponentContainer<PhysXComponent>();

	for (auto entityId : entityIds)
	{
		auto& triggerShape = triggerShapeContainer->Get(entityId);
		auto& physics = physicsContainer->Get(entityId);
		PxRigidActor* pActor = physics.actor;
		if (pActor->isRigidBody()) {
			PxRigidBody* pRigidBody = static_cast<PxRigidBody*>(pActor);
			if (triggerShape.isTriggered && pRigidBody->getRigidBodyFlags().isSet(PxRigidBodyFlag::eKINEMATIC)) {
				triggerShape.pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, false);
				triggerShape.pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				pRigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);
				triggerShape.isTriggered = false;
			}

		}
	}
}

