#include "TestPhysics.h"

#include "GizmosComponent.h"
#include "components/ComponentManager.h"
#include "components/EntityManager.h"
#include "physics/PhysicsComponent.h"
#include "physics/PhysXComponent.h"
#include "physics/PhysXGizmoComponent.h"

#include <PxPhysicsAPI.h>

using namespace reng;
using namespace physx;

void AddPhysXObjects(reng::EntityManager* entityManager, PhysXProcessor* processor)
{
	auto& pose = PxTransform(PxVec3(0), PxQuat(PxHalfPi, PxVec3(0, 0, 1)) );
	auto actor = processor->AddStaticActor(pose, PxPlaneGeometry());
	auto physxEntity = entityManager->Create();
	physxEntity->EmplaceComponent<PhysXComponent>(actor);
	physxEntity->EmplaceComponent<PhysXGizmoComponent>();

	pose = PxTransform( PxVec3(0, 5, 0) );
	actor = processor->AddDynamicActor(pose, PxBoxGeometry(2, 2, 2), 10);
	physxEntity = entityManager->Create();
	physxEntity->EmplaceComponent<PhysXComponent>(actor);
	physxEntity->EmplaceComponent<PhysXGizmoComponent>();

	pose = PxTransform(PxVec3(0, 10, 0));
	actor = processor->AddDynamicActor(pose, PxSphereGeometry(2), 10);
	physxEntity = entityManager->Create();
	physxEntity->EmplaceComponent<PhysXComponent>(actor);
	physxEntity->EmplaceComponent<PhysXGizmoComponent>();
}


void AddPhysicsObjects(reng::EntityManager* entityManager, PhysicsProcessor* processor)
{
	auto boxEntity = entityManager->Create();
	boxEntity->EmplaceComponent<Transform>( glm::vec3(0) );
	boxEntity->EmplaceComponent<RigidbodyComponent>( .1f, glm::vec3(2,5,2) );
	boxEntity->EmplaceComponent<PhysicsComponent>(PhysicsComponent::GemometryType::Box);
	boxEntity->EmplaceComponent<AABBGizmoComponent>(glm::vec3(1, 1, 1), glm::vec4(1, 0, 0, 1));
}
