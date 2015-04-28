
#include "gtest/gtest.h"

#include "IndexedIterator.h"

#include <vector>

using namespace reng;
using namespace std;

TEST(indexed_iterator_test, test_contiguous)
{
	vector<int> container{ 10, 11, 12, 13, 14 };
	vector<uint> index{ 1, 3, 4 };

    std::vector<int>::iterator i1 = container.begin();
    std::vector<uint>::iterator i2 = index.begin();
	IndexedIterator<int,std::vector<int>::iterator,std::vector<uint>::iterator> cont( i1, i2 );

    EXPECT_EQ( *cont, 11 );
    cont++;
    EXPECT_EQ( *cont, 13 );
    cont++;
    EXPECT_EQ( *cont, 14 );
}
