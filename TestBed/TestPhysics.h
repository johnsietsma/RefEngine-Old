#pragma once

namespace reng
{
	class ComponentManager;
	class EntityManager;
	class PhysicsProcessor;
	class PhysXProcessor;
}

namespace physx
{
	class PxPhysics;
	class PxScene;
}

void AddPhysXObjects(reng::EntityManager* entityManager, reng::PhysXProcessor* processor);
void AddPhysicsObjects(reng::EntityManager* entityManager, reng::PhysicsProcessor* processor);

