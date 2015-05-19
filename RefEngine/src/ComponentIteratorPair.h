#pragma once

#include "IndexedIterator.h"

#include <vector>

namespace reng {

template<typename TComponent>
class ComponentIteratorPair
{
public:
	typedef IndexedIterator<TComponent, typename std::vector<TComponent>::iterator, typename std::vector<unsigned int>::iterator> iterator;

	ComponentIteratorPair(std::vector<TComponent>& components, std::vector<unsigned int>& indexes) :
		m_indexes(indexes), // Take a copy, the caller doesn't keep these around.
		begin(components.begin(), m_indexes.begin()),
		end(components.end(), m_indexes.end())
	{
	}

private:
	std::vector<unsigned int> m_indexes;

public:
	iterator begin;
	iterator end;
};

}