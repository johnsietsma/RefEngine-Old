#include "gtest/gtest.h"

#include "ComponentContainer.h"

#include <vector>
#include <stdexcept>
#include <typeinfo>

using namespace reng;

class TestThing 
{
public:
	TestThing(int test) : m_test(test) {}
	int m_test;
};

class TestToo {};


TEST(component_container_test, test_as_type)
{
	auto testThingCont = ComponentContainerTyped<TestThing>();
	ComponentContainer cont = testThingCont; // Store base var

	auto testThingContainer = cont.AsTyped<TestThing>(); // Get derived inst back

	const std::type_info& t1 = typeid(*testThingContainer);
	const std::type_info& t2 = typeid(testThingCont);

	// Surpisingly this doesn't work for different instances! The names are slightly differently managled.
	EXPECT_EQ(t1, t2);

	auto testTooContainer = cont.AsTyped<TestToo>();
	// Programmer error, no guarantees here
	//EXPECT_TRUE(testThingContainer == nullptr);
}

TEST(component_container_test, test_get_first)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	EntityId e2(3);

	EXPECT_THROW(cont.GetFirstComponent(e1), std::out_of_range);

	cont.Add(e2, 5);
	cont.Add(e1, 2);
	cont.Add(e1, 3);

	EXPECT_EQ(cont.GetFirstComponent(e1), 2);

}

TEST(component_container_test, test_get_indexes)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	EntityId e2(2);

	cont.Add(e1, 2);
	cont.Add(e2, 99);
	cont.Add(e1, 3);

	std::vector<uint> indices{ 0, 2 }; // Entity 1 has components at index 0 and 2.
	EXPECT_EQ(cont.GetComponentIndexes(e1), indices );
}

TEST(component_container_test, test_get_entity_id)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	cont.Add(e1, 2);

	EXPECT_EQ(cont.GetEntityId(0), e1); // The component at index 0 belongs to e1.
}

TEST(component_container_test, test_add)
{
	const int id = 3;

	auto testThingCont = ComponentContainerTyped<TestThing>();
	testThingCont.Add(id, 5);
	EXPECT_EQ(testThingCont.GetComponents().size(), 1);

	testThingCont.Add(id, 99);
	EXPECT_EQ(testThingCont.GetComponents().size(), 2);

	EXPECT_EQ(5, testThingCont.GetComponents()[0].m_test);
	EXPECT_EQ(99, testThingCont.GetComponents()[1].m_test);
}

TEST(component_container_test, test_remove)
{
	const int entityId = 0;

	auto cont = ComponentContainerTyped<TestThing>();

	cont.Add(entityId, 5);
	cont.Add(1, 99);

	cont.Remove(entityId);
	EXPECT_EQ(cont.GetComponents().size(), 1);
	EXPECT_EQ(cont.GetComponents()[0].m_test, 99);
}
