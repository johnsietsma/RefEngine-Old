#include "gtest/gtest.h"

#include "ComponentContainer.h"

#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <utility>

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
	ComponentContainerTyped<TestThing> testThingCont = ComponentContainerTyped<TestThing>();
	ComponentContainer& cont = testThingCont; // Store base var

	ComponentContainerTyped<TestThing>* testThingContainer = cont.AsTyped<TestThing>(); // Get derived inst back

	const std::type_info& t1 = typeid(*testThingContainer);
	const std::type_info& t2 = typeid(testThingCont);

	// Surpisingly this doesn't work for different instances! The names are slightly differently managled.
	EXPECT_EQ(t1, t2);

	//ComponentContainerTyped<TestToo>* testTooContainer = cont.AsTyped<TestToo>();
	// Programmer error, no guarantees here
	//EXPECT_TRUE(testThingContainer == nullptr);
}

TEST(component_container_test, test_get_component)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	EntityId e2(2);

	cont.Add(e1, 2);
	cont.Add(e2, 99);
	EXPECT_THROW( cont.Add(e1, 3), std::invalid_argument );

	EXPECT_EQ(cont.Get(e1), 2 );
}

TEST(component_container_test, test_get_entity_id)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	cont.Add(e1, 2);

	EXPECT_EQ(cont.GetEntityId(0), e1); // The component at index 0 belongs to e1.
}

TEST(component_container_test, test_get_indexed_container)
{
	auto cont = ComponentContainerTyped<int>();

	EntityId e1(1);
	EntityId e2(2);
	EntityId e3(3);

	cont.Add(e1, 2);
	cont.Add(e2, 99);
	cont.Add(e3, 3);

    ComponentContainerTyped<int>::iterator_pair iterPair = cont.GetIterators({e1,e3});

	int total = 0;
    
    while( iterPair.first!=iterPair.second)
	{
        total += *iterPair.first;
        iterPair.first++;
	}

	EXPECT_EQ(total, 5); //3+2
}

TEST(component_container_test, test_add)
{
	EntityId id1(1);
	EntityId id2(2);

	auto testThingCont = ComponentContainerTyped<TestThing>();
	testThingCont.Add(id1, 5);
	EXPECT_EQ(testThingCont.GetAll().size(), 1);
	EXPECT_EQ(testThingCont.GetEntityIds().size(), 1);

	testThingCont.Add(id2, 99);
	EXPECT_EQ(testThingCont.GetAll().size(), 2);
	EXPECT_EQ(testThingCont.GetEntityIds().size(), 2);

	EXPECT_EQ(5, testThingCont.GetAll()[0].m_test);
	EXPECT_EQ(99, testThingCont.GetAll()[1].m_test);
}

TEST(component_container_test, test_remove)
{
	const int entityId = 0;

	auto cont = ComponentContainerTyped<TestThing>();

	cont.Add(entityId, 5);
	cont.Add(1, 99);

	cont.Remove(entityId);
	EXPECT_EQ(cont.GetAll().size(), 1);
	EXPECT_EQ(cont.GetEntityIds().size(), 1);
	EXPECT_EQ(cont.GetAll()[0].m_test, 99);
}
