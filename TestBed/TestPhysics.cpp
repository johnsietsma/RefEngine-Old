#include "TestPhysics.h"

#include "components/ComponentManager.h"
#include "physics/PhysXPhysics.h"

#include <PxPhysicsAPI.h>

using namespace reng;
using namespace physx;

void AddPhysicsObjects(reng::ComponentManager* componentManager, PhysXProcessor* processor)
{
	auto physicsContainer = componentManager->GetComponentContainer<PxActor*>();
	auto& pose = PxTransform(PxVec3(0), PxQuat(PxHalfPi, PxVec3(0, 0, 1)) );

	auto actor = processor->AddStaticActor(pose, PxPlaneGeometry());
	physicsContainer->Add(-1, actor);

	pose = PxTransform( PxVec3(0, 5, 0) );
	actor = processor->AddDynamicActor(pose, PxBoxGeometry(2, 2, 2), 10);
}
