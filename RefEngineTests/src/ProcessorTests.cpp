
#include "gtest/gtest.h"

#include <ProcessorManager.h>

#include <string>
#include <vector>

using namespace reng;

void ProcessTest1(const std::vector<int>& items, bool& hasProcessed)
{
	hasProcessed = true;
}

TEST(processor_test, test_one_arg)
{
	bool hasProcessed = false;
	Processor<int,bool&> proc( ProcessTest1 );

	std::vector<int> v{ 1, 2, 3 };
	proc.Process(v, hasProcessed);

	EXPECT_TRUE(hasProcessed);
}