
#include "gtest/gtest.h"

#include "components/Processor.h"

#include <string>
#include <vector>

using namespace reng;

struct Transform {
	bool processed;
};

struct SpinComponent {
	SpinComponent() = default;
	SpinComponent(int s) : spinSpeed(s) {}
	int spinSpeed;
};


struct SpinProcessor : reng::Processor<SpinComponent>
{
	void DoProcess( const std::vector<EntityId>& entityIds, ComponentManager& componentManager)
	{
		auto transformContainer = componentManager.GetComponentContainer<Transform>();
		auto spinContainer = componentManager.GetComponentContainer<SpinComponent>();

		for (auto entityId : entityIds)
		{
			Transform& transform = transformContainer->Get(entityId);
			SpinComponent& spin = spinContainer->Get(entityId);
			transform.processed = true;
		}
	}
};

TEST(processor_test, test_process)
{
	ComponentManager cm;

	EntityId id1(1);
	EntityId id2(2);

	cm.GetComponentContainer<Transform>()->Emplace(id1);

	cm.GetComponentContainer<Transform>()->Emplace(id2);
	cm.GetComponentContainer<SpinComponent>()->Emplace(id2);

	SpinProcessor spinProcessor;
	EXPECT_FALSE(cm.GetComponentContainer<Transform>()->GetAll()[0].processed);
	EXPECT_FALSE(cm.GetComponentContainer<Transform>()->GetAll()[1].processed);

	spinProcessor.Process(cm);

	EXPECT_FALSE(cm.GetComponentContainer<Transform>()->GetAll()[0].processed); // Only transforms with spins are processed
	EXPECT_TRUE(cm.GetComponentContainer<Transform>()->GetAll()[1].processed);
}

void ProcessTest1(const std::vector<int>& items, bool& hasProcessed)
{
	hasProcessed = true;
}
