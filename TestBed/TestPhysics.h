#pragma once

namespace reng
{
	class ComponentManager;
	class PhysXProcessor;
}

namespace physx
{
	class PxPhysics;
	class PxScene;
}

void AddPhysicsObjects(reng::ComponentManager* componentManager, reng::PhysXProcessor* processor);

