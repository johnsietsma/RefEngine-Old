
#include "gtest/gtest.h"

#include <ComponentManager.h>

#include <string>

using namespace reng;

class TestThing1{};

TEST(component_manager_test, test_add)
{
	ComponentManager componentManager;

	EXPECT_EQ(0, componentManager.GetNumberOfComponents<TestThing1>());
	componentManager.AddComponent<TestThing1>(1);
	EXPECT_EQ(1, componentManager.GetNumberOfComponents<TestThing1>());
}
