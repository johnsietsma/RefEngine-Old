
#include "gtest/gtest.h"

#include <ComponentManager.h>
#include <IndexedContainer.h>

#include <string>
#include <vector>

using namespace reng;

class TestThing1{};


class Component {
public:
	EntityId entityId;
};

class Transform : Component {};

struct SpinComponent : Component {
	Transform* pTransform;
	GameTime* pTime;
};



TEST(component_manager_test, test_add)
{
	IndexedContainerTyped<SpinComponent> spinContainer;
	IndexedContainerTyped<Transform> transformContainer;

	spinContainer.Add(0);
	transformContainer.Add(0);

	transformContainer.Add(1);

	spinContainer.Add(2);
	transformContainer.Add(2);


	std::vector<SpinComponent>& spinComponents = spinContainer.GetAll();

	for(auto spinComponent : spinComponents)
	{
		Transform& t = transformContainer.GetFirst(spinComponent.entityId.Value());
	}
}
