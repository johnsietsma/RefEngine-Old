#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"

#include <glm/fwd.hpp>

namespace physx
{
	class PxRigidActor;
	class PxAllocatorCallback;
	class PxErrorCallback;
	class PxFoundation;
	class PxGeometry;
	class PxMaterial;
	class PxPhysics;
	class PxScene;
	class PxTransform;

}

namespace reng {

class GameTime;

struct PhysXComponent
{
	PhysXComponent(const physx::PxRigidActor* a_actor) : actor(a_actor)
	{}

	const physx::PxRigidActor* actor;
};

class PhysXProcessor : public reng::Processor<PhysXComponent, GameTime>
{
public:
	PhysXProcessor();
	~PhysXProcessor();

	void InitVisualDebugger();

	physx::PxPhysics* GetPhysics() { return m_physics;  }
	physx::PxScene* GetScene() { return m_scene;  }

	physx::PxRigidActor* AddStaticActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry);
	physx::PxRigidActor* AddDynamicActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry, float density);

	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager, GameTime& time) override;

private:
	physx::PxAllocatorCallback* m_allocator;
	physx::PxErrorCallback* m_errorCallback;
	physx::PxFoundation* m_foundation;
	physx::PxPhysics* m_physics;
	physx::PxScene* m_scene;
	physx::PxMaterial* m_material;
};

}