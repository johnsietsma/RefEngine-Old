
#include "gtest/gtest.h"

#include <ComponentManager.h>
#include <ComponentContainer.h>

#include <algorithm>
#include <functional>
#include <string>
#include <typeindex>
#include <vector>

using namespace reng;


template<typename TFirst, typename TSecond>
class dual_vector
{
public:
	typedef std::vector<TFirst> first_type;
	typedef std::vector<TSecond> second_type;

	typename first_type::iterator to_first(typename second_type::iterator second_it) {
		return to_other_inner<second_type,first_type>(second_it, second.begin(), first.begin());
	}

	typename second_type::iterator to_second(typename first_type::iterator first_it) {
		return to_other_inner<first_type,second_type>(first_it, first.begin(), second.begin());
	}

	template<typename ...TSecondArgs>
	std::tuple<TFirst&,TSecond&> emplace( TFirst firstValue, TSecondArgs... secondArgs )
	{
		first.push_back(firstValue);
		second.emplace_back(secondArgs...);
		return std::tie(first.back(), second.back());
	}

	first_type first;
	second_type second;
private:
	template<typename TOrig, typename TOther>
	typename TOther::iterator to_other_inner(typename TOrig::iterator orig_inner_itr, typename TOrig::iterator orig_inner_begin, typename TOther::iterator other_inner_begin) {
		return other_inner_begin + (orig_inner_itr - orig_inner_begin);
	}
};

struct TestThing1
{
	TestThing1() = default;
	TestThing1(int v) : val(v) {}
	int val;
};

struct Transform {
	bool processed;
};

struct SpinComponent {
	SpinComponent() = default;
	SpinComponent(int s) : spinSpeed(s) {}
	int spinSpeed;
};

void ProcessFunc( ComponentIteratorPair<SpinComponent> spinIters,
				  ComponentIteratorPair<Transform> transformIters )
{
	while( spinIters.begin!=spinIters.end)
	{
        SpinComponent& spin = *spinIters.begin;
		Transform& t = *transformIters.begin;
		t.processed = true;
        spinIters.begin++;
        transformIters.begin++;
	}
}

TEST(dual_vector_test, test)
{
	typedef dual_vector<int, TestThing1> TestDualVector;
	TestDualVector dualVector;
	auto p = dualVector.emplace(1, 10);

	TestThing1& tt = std::get<1>(p);
	tt.val = 99;
	EXPECT_EQ(dualVector.second.begin()->val, 99);

	dualVector.emplace(2, 20);

	TestDualVector::first_type::iterator fItr = std::find(dualVector.first.begin(), dualVector.first.end(), 2);
	EXPECT_FALSE(fItr == dualVector.first.end());

	dualVector.emplace(2, 30);

	fItr = dualVector.to_first( dualVector.second.begin() );
	EXPECT_EQ(*fItr, 1);

}


TEST(component_manager_test, test_process)
{
	ComponentManager cm;

	EntityId id1(1);
	EntityId id2(2);

	cm.AddComponent<SpinComponent>(id1);

	cm.AddComponent<Transform>(id1);
	cm.AddComponent<Transform>(id2);

	cm.AddComponent<SpinComponent>(id2);

	EXPECT_FALSE( cm.GetComponents<Transform>()[0].processed );

    std::function< void(ComponentIteratorPair<SpinComponent>, ComponentIteratorPair<Transform>) > f = ProcessFunc;
	cm.Process<SpinComponent, Transform>(f);

	EXPECT_TRUE(cm.GetComponents<Transform>()[0].processed);
}

TEST(component_manager_test, test_get_component)
{
	ComponentManager cm;
	EntityId id1(1);
	EntityId id2(2);

	SpinComponent& spin = cm.AddComponent<SpinComponent>(id1, 5);
	EXPECT_EQ(cm.GetComponent<SpinComponent>(id1).spinSpeed, 5);
	spin.spinSpeed = 4;
	EXPECT_EQ(cm.GetComponent<SpinComponent>(id1).spinSpeed, 4);

	cm.AddComponent<SpinComponent>(id2, 10);

	EXPECT_EQ(cm.GetComponents<SpinComponent>().size(), 2);
}
