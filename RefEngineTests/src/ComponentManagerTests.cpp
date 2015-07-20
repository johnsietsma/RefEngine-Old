
#include "gtest/gtest.h"

#include "components/ComponentManager.h"
#include "components/ComponentContainer.h"
#include "components/Processor.h"

#include <algorithm>
#include <functional>
#include <string>
#include <typeindex>
#include <vector>

using namespace reng;

struct Transform {
};

struct SpinComponent {
	SpinComponent() = default;
	SpinComponent(int s) : spinSpeed(s) {}
	int spinSpeed;
};


TEST(component_manager_test, test_get_component)
{
	ComponentManager cm;
	EntityId id1(1);
	EntityId id2(2);

	auto spinContainer = cm.GetComponentContainer<SpinComponent>();
	SpinComponent& spin = spinContainer->Emplace(id1, 5);
	EXPECT_EQ(spinContainer->Get(id1).spinSpeed, 5);
	spin.spinSpeed = 4;
	EXPECT_EQ(cm.GetComponentContainer<SpinComponent>()->Get(id1).spinSpeed, 4);

	spinContainer->Emplace(id2, 10);

	EXPECT_EQ(cm.GetComponentContainer<SpinComponent>()->GetAll().size(), 2);
}
