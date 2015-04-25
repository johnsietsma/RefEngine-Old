
#include "gtest/gtest.h"

#include <ComponentManager.h>
#include <ComponentContainer.h>

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
	ComponentContainerTyped<SpinComponent> spinContainer;
	ComponentContainerTyped<Transform> transformContainer;

	spinContainer.Add(0);
	transformContainer.Add(0);

	transformContainer.Add(1);

	spinContainer.Add(2);
	transformContainer.Add(2);


	std::vector<SpinComponent>& spinComponents = spinContainer.GetComponents();

	for(auto spinComponent : spinComponents)
	{
		Transform& t = transformContainer.GetFirstComponent(spinComponent.entityId.Value());
	}
}
