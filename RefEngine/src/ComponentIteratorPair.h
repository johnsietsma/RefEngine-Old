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
		m_components(components),
		m_indexes(indexes) // Take a copy, the caller doesn't keep these around.
	{
	}

	iterator begin()
	{
		return iterator(m_components.begin(),m_indexes.begin());
	}

	iterator end()
	{
		return iterator(m_components.end(), m_indexes.end());
	}

private:
	std::vector<TComponent>& m_components;
	std::vector<unsigned int> m_indexes;

};

}