
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
	Transform* pTransform;
	GameTime* pTime;
};

void ProcessFunc(
	IndexedContainer<SpinComponent> spins,
	IndexedContainer<Transform> transforms)
{

	for (uint i = 0; i < transforms.Size(); i++)
	{
		SpinComponent& spin = spins.Get(i);
		Transform& t = transforms.Get(i);
		t.processed = true;
	}
}

TEST(component_manager_test, test_process)
{
	ComponentManager cm;

	ComponentContainerTyped<SpinComponent>* spinContainer = cm.GetComponentContainer<SpinComponent>();
	ComponentContainerTyped<Transform>* transformContainer = cm.GetComponentContainer<Transform>();

	spinContainer->Add(0);
	transformContainer->Add(0);

	transformContainer->Add(1);

	spinContainer->Add(2);
	transformContainer->Add(2);

	EXPECT_FALSE( transformContainer->GetComponents()[0].processed );

	std::function< void(IndexedContainer<SpinComponent>, IndexedContainer<Transform>) > f = ProcessFunc;
	cm.Process<SpinComponent, Transform>(f);

	EXPECT_TRUE(transformContainer->GetComponents()[0].processed);
}

TEST(component_manager_test, test_get_component_manager)
{
	ComponentManager cm;

	EXPECT_EQ(cm.GetNumberOfComponentContainers(), 0);

	ComponentContainerTyped<SpinComponent>* spinContainer = cm.GetComponentContainer<SpinComponent>();

	EXPECT_EQ(spinContainer->GetComponents().size(), 0);
	spinContainer->Add(0);

	EXPECT_EQ(spinContainer->GetComponents().size(), 1);
	EXPECT_EQ(cm.GetComponentContainer<SpinComponent>()->GetEntityIds().size(), 1);


	ComponentContainerTyped<Transform>* transformContainer = cm.GetComponentContainer<Transform>();

	EXPECT_EQ(cm.GetNumberOfComponentContainers(), 2);
}
