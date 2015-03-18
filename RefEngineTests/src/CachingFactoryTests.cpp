
#include "gtest/gtest.h"

#include <CachingFactory.h>

#include <string>

using namespace reng;

// This thing we will create in the factory
struct TestThing {};

// Create the thing will no params
TestThing* MakeTest1() {
	return new TestThing();
}

// Create the thing with more params
TestThing* MakeTest2(std::string p1, int p2, TestThing* p3) {
	(void*)p3;
	return new TestThing();
}


TEST(caching_factory_test, test_get_no_params)
{
	CachingFactory<TestThing*> cf(MakeTest1);
	TestThing* t1 = cf.Get();
	EXPECT_NE(t1, nullptr);
}


TEST(caching_factory_test, test_get_multiple_params)
{
	TestThing* pTestThing = new TestThing();
	CachingFactory<TestThing*,std::string,int,TestThing*> cf(MakeTest2);

	// Test we're caching the same object
	TestThing* t1 = cf.Get(std::string("a"), 1, pTestThing);
	EXPECT_NE(t1, nullptr);

	TestThing* t2 = cf.Get(std::string("a"), 1, pTestThing);
	EXPECT_EQ(t1, t2);

	// Vary paramters and check we get different objects
	TestThing* t3 = cf.Get(std::string("b"), 1, pTestThing);
	EXPECT_NE(t1, t3);

	TestThing* t4 = cf.Get(std::string("a"), 2, pTestThing);
	EXPECT_NE(t1, t4);

	//TestThing* pNullThing = nullptr;
	//TestThing* t5 = cf.Get(std::string("a"), 1, pNullThing);
	//EXPECT_NE(t1, t5);
}
