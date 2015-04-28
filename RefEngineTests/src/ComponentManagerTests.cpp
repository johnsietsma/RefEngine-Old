
#include "gtest/gtest.h"

#include <ComponentManager.h>
#include <ComponentContainer.h>

#include <algorithm>
#include <functional>
#include <string>
#include <typeindex>
#include <vector>

using namespace reng;

class TestThing1{};
struct Transform {
	bool processed;
};

struct SpinComponent {
	SpinComponent() = default;
	SpinComponent(int s) : spinSpeed(s) {}
	int spinSpeed;
};

void ProcessFunc(
                 ComponentContainerTyped<SpinComponent>::iterator_pair spinIters,
                 ComponentContainerTyped<Transform>::iterator_pair transformIters
                 )
{

	while( spinIters.first!=spinIters.second)
	{
        SpinComponent& spin = *spinIters.first;
		Transform& t = *transformIters.first;
		t.processed = true;
        spinIters.first++;
        transformIters.first++;
	}
}

TEST(component_manager_test, test_process)
{
	ComponentManager cm;

	EntityId id1(1);
	EntityId id2(2);

	cm.AddComponent<SpinComponent>(id1);

	cm.AddComponent<Transform>(id1);
	cm.AddComponent<Transform>(id2);

	cm.AddComponent<SpinComponent>(id2);

	EXPECT_FALSE( cm.GetComponents<Transform>()[0].processed );

    std::function< void(ComponentContainerTyped<SpinComponent>::iterator, ComponentContainerTyped<Transform>::iterator) > f = ProcessFunc;
	cm.Process<SpinComponent, Transform>(f);

	EXPECT_TRUE(cm.GetComponents<Transform>()[0].processed);
}

TEST(component_manager_test, test_get_component)
{
	ComponentManager cm;
	EntityId id1(1);
	EntityId id2(2);

	SpinComponent& spin = cm.AddComponent<SpinComponent>(id1, 5);
	EXPECT_EQ(cm.GetComponent<SpinComponent>(id1).spinSpeed, 5);
	spin.spinSpeed = 4;
	EXPECT_EQ(cm.GetComponent<SpinComponent>(id1).spinSpeed, 4);

	cm.AddComponent<SpinComponent>(id2, 10);

	EXPECT_EQ(cm.GetComponents<SpinComponent>().size(), 2);
}
