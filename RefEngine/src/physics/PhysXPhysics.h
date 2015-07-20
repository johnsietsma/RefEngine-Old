#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"

#include <glm/fwd.hpp>

namespace physx
{
	class PxActor;
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
	PhysXComponent(
		const physx::PxTransform& transform,
		const physx::PxGeometry& geometry,
		const physx::PxMaterial& material,
		float density);

	physx::PxActor* actor;
};

class PhysXProcessor : public reng::Processor<PhysXComponent, GameTime>
{
public:
	PhysXProcessor();
	~PhysXProcessor();

	void InitVisualDebugger();

	physx::PxPhysics* GetPhysics() { return m_physics;  }
	physx::PxScene* GetScene() { return m_scene;  }

	physx::PxActor* AddStaticActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry);
	physx::PxActor* AddDynamicActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry, float density);

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