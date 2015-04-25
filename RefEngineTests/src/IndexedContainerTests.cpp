
#include "gtest/gtest.h"

#include "IndexedContainer.h"

#include <vector>

using namespace reng;
using namespace std;

TEST(indexed_container_test, test_contiguous)
{
	vector<int> container{ 10, 11, 12, 13 };
	vector<uint> index{ 1, 2, 3 };


	IndexedContainer<int> cont( index, container );

	EXPECT_EQ(cont.Get(0), 11);
	EXPECT_EQ(cont.Get(1), 12);
	EXPECT_EQ(cont.Get(2), 13);
}