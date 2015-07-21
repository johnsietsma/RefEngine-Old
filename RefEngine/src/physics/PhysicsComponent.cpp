
#include "GameTime.h"
#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "physics/PhysicsComponent.h"

#include "utils/pow2assert.h"

using namespace reng;



void PhysicsProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager, GameTime& time)
{
	auto physicsContainer = componentManager.GetComponentContainer<PhysicsComponent>();
	auto rigidbodyContainer = componentManager.GetComponentContainer<RigidbodyComponent>();
	auto transformContainer = componentManager.GetComponentContainer<Transform>();

	for (auto entityId : entityIds)
	{
		auto& physics = physicsContainer->Get(entityId);

		POW2_ASSERT(rigidbodyContainer->Has(entityId));
		POW2_ASSERT(transformContainer->Has(entityId));

		auto& rigidbody = rigidbodyContainer->Get(entityId);
		auto& transform = transformContainer->Get(entityId);

		transform.Translate( rigidbody.velocity * (float)time.deltaTime );
	}
}
