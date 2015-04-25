
#include "gtest/gtest.h"

#include <ComponentManager.h>
#include <ComponentContainer.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace reng;

class TestThing1{};
class Transform {};

struct SpinComponent {
	Transform* pTransform;
	GameTime* pTime;
};

void ProcessFunc(
	IndexedContainer<Transform>& transforms,
	IndexedContainer<SpinComponent>& spins)
{

	for (uint i = 0; i < transforms.Size(); i++)
	{
		SpinComponent& spin = spins.Get(i);
		Transform& t = transforms.Get(i);
	}
}

TEST(component_manager_test, test_add)
{
	ComponentContainerTyped<SpinComponent> spinContainer;
	ComponentContainerTyped<Transform> transformContainer;

	spinContainer.Add(0);
	transformContainer.Add(0);

	transformContainer.Add(1);

	spinContainer.Add(2);
	transformContainer.Add(2);

	const std::vector<EntityId>& entityIds = spinContainer.GetEntityIds();
	IndexedContainer<Transform> transforms = transformContainer.GetIndexedContainer(entityIds);
	IndexedContainer<SpinComponent> spins = spinContainer.GetIndexedContainer(entityIds);

	ProcessFunc(transforms, spins);
}
