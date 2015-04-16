#include "gtest/gtest.h"

#include "IndexedContainer.h"

#include <vector>
#include <typeinfo>

class TestThing 
{
public:
	TestThing(int test) : m_test(test) {}
	int m_test;
};

class TestToo {};

TEST(indexed_component_test, test_get)
{
	const int id = 3;

	auto indexedCont = IndexedContainerTyped<TestThing>();
	indexedCont.Add(id, 5);
	EXPECT_EQ(indexedCont.GetIndexes(id).size(), 1);

	indexedCont.Add(id, 99);
	EXPECT_EQ(indexedCont.GetIndexes(id).size(), 2);

	EXPECT_EQ(5, indexedCont.Get(0).m_test);
	EXPECT_EQ(99, indexedCont.Get(1).m_test);
}

TEST(indexed_component_test, test_as_type)
{
	auto indexedCont = IndexedContainerTyped<TestThing>();
	IndexedContainer cont = indexedCont;

	auto testThingContainer = cont.AsTyped<TestThing>();

	const std::type_info& t1 = typeid(*testThingContainer);
	const std::type_info& t2 = typeid(indexedCont);

	// Surpisingly this doesn't work for different instances! The names are slightly differently managled.
	EXPECT_EQ(t1,t2);

	auto testTooContainer = cont.AsTyped<TestToo>();
	// Programmer error, no guarantees here
	//EXPECT_TRUE(testThingContainer == nullptr);
}


TEST(indexed_component_test, test_add_and_remove)
{
	const int entityId = 0;

	auto cont = IndexedContainerTyped<TestThing>();

	EXPECT_EQ(cont.Size(), 0);

	TestThing& testThing = cont.Add(entityId, 5);
	EXPECT_EQ(cont.Size(), 1);

	EXPECT_EQ(testThing.m_test, 5);

	cont.Remove(entityId);
	EXPECT_EQ(cont.Size(), 0);
}
