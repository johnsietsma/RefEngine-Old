#include "PhysXGizmoComponent.h"
#include "PhysXComponent.h"
#include "GameTime.h"
#include "components/Entity.h"
#include "components/ComponentManager.h"

#include <aie/gizmos.h>

#include "utils/pow2assert.h"

#include <PxPhysicsAPI.h>

using namespace reng;
using namespace physx;

void AddBox(PxShape* shape, const PxRigidActor* actor)
{
	PxBoxGeometry geometry;
	float width = 1, height = 1, length = 1;
	if (!shape->getBoxGeometry(geometry)) return;
	glm::vec3 extents(geometry.halfExtents.x, geometry.halfExtents.y, geometry.halfExtents.z);
	PxMat44 m(PxShapeExt::getGlobalPose(*shape, *actor));
	glm::mat4x4 M(
		m.column0.x, m.column0.y, m.column0.z, m.column0.w,
		m.column1.x, m.column1.y, m.column1.z, m.column1.w,
		m.column2.x, m.column2.y, m.column2.z, m.column2.w,
		m.column3.x, m.column3.y, m.column3.z, m.column3.w
		);

	PxVec3 p = m.getPosition();
	glm::vec3 pos(p.x, p.y, p.z);

	Gizmos::addAABBFilled(pos, extents, glm::vec4(0, 1, 0, 1), &M);

}


void AddPlane(PxShape* shape, const PxRigidActor* actor)
{
	PxTransform transform(PxShapeExt::getGlobalPose(*shape, *actor));

	PxMat44 m(PxShapeExt::getGlobalPose(*shape, *actor));
	glm::mat4x4 M(
		m.column0.x, m.column0.y, m.column0.z, m.column0.w,
		m.column1.x, m.column1.y, m.column1.z, m.column1.w,
		m.column2.x, m.column2.y, m.column2.z, m.column2.w,
		m.column3.x, m.column3.y, m.column3.z, m.column3.w
		);

	PxVec3 p = m.getPosition();
	glm::vec3 pos(p.x, p.y, p.z);

	Gizmos::addAABBFilled(pos, glm::vec3(0,10,10), glm::vec4(0, 0, 1, 1), &M);
}


void AddSphere(PxShape* shape, const PxRigidActor* actor)
{
	PxTransform transform(PxShapeExt::getGlobalPose(*shape, *actor));

	PxSphereGeometry geometry;
	if (!shape->getSphereGeometry(geometry))  return;

	PxMat44 m(PxShapeExt::getGlobalPose(*shape, *actor));
	glm::vec3 pos(m[3][0], m[3][1], m[3][2]);

	Gizmos::addSphere(pos, geometry.radius, 10, 10, glm::vec4(1, 0, 0, 1));
}


void AddWidget(PxShape* shape, const PxRigidActor* actor)
{
	PxGeometryType::Enum type = shape->getGeometryType();
	switch (type)
	{
	case PxGeometryType::eBOX:
		AddBox(shape, actor);
		break;
	case PxGeometryType::ePLANE:
		AddPlane(shape, actor);
	case PxGeometryType::eSPHERE:
		AddSphere(shape, actor);
	}

}

void PhysXGizmoComponent::AddActorShapes(const PxRigidActor* actor)
{
	PxU32 nShapes = actor->getNbShapes();
	PxShape** shapes = new PxShape*[nShapes];
	actor->getShapes(shapes, nShapes);

	while(nShapes--)
	{
		AddWidget(shapes[nShapes], actor);
	}

	delete shapes;
}

void PhysXGizmoProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager)
{
	auto gizmosContainer = componentManager.GetComponentContainer<PhysXGizmoComponent>();
	auto physxContainer = componentManager.GetComponentContainer<PhysXComponent>();

	Gizmos::clear();

	for (auto entityId : entityIds)
	{
		auto& gizmo = gizmosContainer->Get(entityId);
		auto& physxComponent = physxContainer->Get(entityId);
		gizmo.AddActorShapes(physxComponent.actor);
	}
}
