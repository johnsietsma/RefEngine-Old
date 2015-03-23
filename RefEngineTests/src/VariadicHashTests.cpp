
#include "gtest/gtest.h"

#include <VariadicHash.h>

#include <algorithm>
#include <string>

using namespace reng;

struct TestThing{};

TEST(vhash_test, test_no_params)
{
	EXPECT_EQ(0, vhash());
}


TEST(vhash_test, test_one_int)
{
	EXPECT_EQ(std::hash<int>()(5), vhash(5));
}


TEST(vhash_test, test_one_string)
{
	EXPECT_EQ(std::hash<std::string>()("a"), vhash(std::string("a")));
	EXPECT_NE(std::hash<std::string>()("a"), vhash(std::string("b")));
}


TEST(vhash_test, test_null_ptr)
{
	TestThing* pThing = nullptr;
	EXPECT_EQ(vhash(pThing), vhash(pThing));
	EXPECT_NE(vhash(new TestThing()), vhash(pThing));
}

TEST(vhash_test, test_two)
{
	size_t hash1 = vhash(std::string("a"), 1);
	size_t hash2 = vhash(std::string("a"), 1);
	size_t hash3 = vhash(std::string("a"), 2);
	EXPECT_EQ(hash1, hash2);
	EXPECT_NE(hash1, hash3);
}


TEST(vhash_test, test_two_object)
{
	TestThing* pThing = new TestThing();
	TestThing* pNullThing = nullptr;
	size_t hash1 = vhash(std::string("a"), pThing);
	size_t hash2 = vhash(std::string("a"), pNullThing);
	EXPECT_NE(hash1, hash2);
}

TEST(vhash_test, test_three)
{
	size_t hash1 = vhash(std::string("a"), 1, 1);
	size_t hash2 = vhash(std::string("a"), 1, 2);
	EXPECT_NE(hash1, hash2);
}

TEST(vhash_test, test_three_object)
{
	TestThing* pThing1 = new TestThing();
	TestThing* pThing2 = new TestThing();
	size_t hash1 = vhash(std::string("a"), 1, pThing1);
	size_t hash2 = vhash(std::string("a"), 1, pThing2);
	EXPECT_NE(hash1, hash2);
}


