
#include "GameTime.h"
#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "physics/PhysXComponent.h"
#include "utils/memaligned.h"

#include <PxPhysicsAPI.h>

#include <iostream>

using namespace reng;
using namespace physx;

class AlignedAllocatorCallback : public PxAllocatorCallback
{
	void* allocate(size_t size, const char* typeName, const char* filename, int line) override
	{
		return aligned_malloc(size, 16);
	}

	void deallocate(void* ptr)
	{
		return aligned_free(ptr);
	}
};

class ConsoleErrorCallback : public PxErrorCallback
{
	void reportError(PxErrorCode::Enum errorCode, const char* message, const char* file, int line)
	{
		std::cout << file << "(" << line << "): PhysX Error (" << errorCode << "): " << message;
	}
};

PhysXComponent::PhysXComponent(const PxTransform& transform, const PxGeometry& geometry, const PxMaterial& material, float density)
{
}



PhysXProcessor::PhysXProcessor() :
	m_allocator(new AlignedAllocatorCallback()),
	m_errorCallback(new ConsoleErrorCallback()),
	m_foundation(PxCreateFoundation(PX_PHYSICS_VERSION, *m_allocator, *m_errorCallback)),
	m_physics(PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale())),
	m_material(m_physics->createMaterial(0.5f,0.5f,0.5f))
{
	PxInitExtensions(*m_physics);
	PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.f, 0);
	sceneDesc.filterShader = &PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	m_scene = m_physics->createScene(sceneDesc);
}

PhysXProcessor::~PhysXProcessor()
{
	m_scene->release();
	m_physics->release();
	m_foundation->release();
	delete m_errorCallback;
	delete m_allocator;
}

void PhysXProcessor::InitVisualDebugger()
{
	auto connectionManager = m_physics->getPvdConnectionManager();
	if( connectionManager == nullptr) return;

	PxVisualDebuggerConnectionFlags flags = PxVisualDebuggerExt::getAllConnectionFlags();
	auto connection = PxVisualDebuggerExt::createConnection(connectionManager, "127.0.0.1", 5425, 100, flags);
}


physx::PxActor* PhysXProcessor::AddStaticActor( const PxTransform& transform, const PxGeometry& geometry )
{
	auto actor = PxCreateStatic(*m_physics, transform, geometry, *m_material);
	m_scene->addActor(*actor);
	return actor;

}

physx::PxActor* PhysXProcessor::AddDynamicActor(const PxTransform& transform, const PxGeometry& geometry, float density)
{
	auto actor = PxCreateDynamic(*m_physics, transform, geometry, *m_material, density);
	m_scene->addActor(*actor);
	return actor;

}


void PhysXProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager, GameTime& time)
{
	m_scene->simulate((PxReal)time.deltaTime);
	while (!m_scene->fetchResults())
	{
		// no-op
	}

	auto physicsContainer = componentManager.GetComponentContainer<PhysXComponent>();

	for (auto entityId : entityIds)
	{
		auto& physics = physicsContainer->Get(entityId);
	}
}
