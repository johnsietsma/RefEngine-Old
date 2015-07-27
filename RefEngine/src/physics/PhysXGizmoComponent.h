#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "Transform.h"

#include <glm/fwd.hpp>

namespace physx {
	class PxRigidActor;
	class PxShape;
}

namespace reng {

class GameTime;


struct PhysXGizmoComponent
{
	void AddActorShapes(const physx::PxRigidActor* actor);
};


class PhysXGizmoProcessor : public reng::Processor<PhysXGizmoComponent>
{
public:
	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager) override;
};

}
