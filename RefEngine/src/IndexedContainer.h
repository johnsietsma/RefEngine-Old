#pragma once

#include "types.h"
#include "pow2assert.h"

#include <vector>


namespace reng {


/*! An IndexedContainer provides an index along with a plain container to allow
	indexing the container in a non-contiguous way.

	For exmaple, an container with unused elements, could have an index that
	skipped the unsed slots. So, if the container contained the value [9, 4, 5, 3] 
	and the user would like	to walk though the container without using the 2nd 
	elements, then the index would be [0,2,3], and Get(2) would return the value '3';
*/
template<typename T>
class IndexedContainer
{
public:
	IndexedContainer(std::vector<uint> indexes, std::vector<T>& container) :
		m_indexes(indexes),
		m_container(container)
	{}

	//! Return the number of indexes into the container.
	uint Size() const 
	{
		return m_indexes.size();
	}

	// Get the 'i'th element that has been indexed.
	inline T& Get(uint i)
	{
		POW2_ASSERT(i < m_indexes.size());
		POW2_ASSERT(m_indexes[i] < m_container.size());
		return m_container.at(m_indexes[i]);
	}

private:
	std::vector<uint> m_indexes;
	std::vector<T>& m_container;
};



}