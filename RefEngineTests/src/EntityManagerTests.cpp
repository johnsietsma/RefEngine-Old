#include "components/EntityManager.h"

#include "gtest/gtest.h"

using namespace reng;

TEST(entity_manager_test, test_add)
{
	EntityManager em;
	EXPECT_EQ(em.GetNumberOfEntites(), 0);
}
