#include "GizmosComponent.h"
#include "GameTime.h"
#include "components/Entity.h"
#include "components/ComponentManager.h"

#include <aie/gizmos.h>

#include "utils/pow2assert.h"

using namespace reng;



void AABBGizmoProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager)
{
	auto gizmosContainer = componentManager.GetComponentContainer<AABBGizmoComponent>();
	auto transformContainer = componentManager.GetComponentContainer<Transform>();

	Gizmos::clear();

	for (auto entityId : entityIds)
	{
		auto& gizmo = gizmosContainer->Get(entityId);

		POW2_ASSERT(transformContainer->Has(entityId));
		auto& transform = transformContainer->Get(entityId);

		Gizmos::addAABBFilled(transform.GetPosition(), gizmo.extents, gizmo.color);
	}
}
