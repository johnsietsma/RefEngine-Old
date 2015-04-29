#pragma once

#include <iterator>
#include <vector>

namespace reng {

/*! An IndexedIterator provides an index along with a plain iterator to allow
	indexing the iterator in a non-contiguous way.

	For example an container with unused elements, could have an index that
	skipped the unsed slots. So, if the container contained the value [9, 4, 5, 3]
	and the user would like	to walk though the container without using the 2nd
	elements, then the index would be [0,2,3], and Get(2) would return the value '3';
*/
template<typename T, typename TIterator, typename TIndexIterator>
class IndexedIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    typedef IndexedIterator<T,TIterator,TIndexIterator> IndexedIterator_t;

    IndexedIterator(TIterator iter, TIndexIterator indexIter) :
    	m_iter(iter),
    	m_indexIter(indexIter)
    {}

    bool operator==(const IndexedIterator_t& rhs) const { return m_indexIter==rhs.m_indexIter; }
    bool operator!=(const IndexedIterator_t& rhs)const { return !(*this==rhs); }

    IndexedIterator_t& operator++() { m_indexIter++; }
    IndexedIterator_t operator++(int) { auto temp(*this); ++m_indexIter; return temp; }
    IndexedIterator_t& operator--() { --m_indexIter; return (*this); }
    IndexedIterator_t operator--(int) { auto temp(*this); --m_indexIter; return temp; }

    T& operator*() { return m_iter[*m_indexIter]; } // Do the double lookup. The index and then the element.
    const T& operator*() const { return m_iter[*m_indexIter]; }
    T* operator->(){return &*this;}
    T* getPtr()const{return &*this;}
    const T* getConstPtr()const{return &*this;}

protected:

	TIterator m_iter; // The underlying container
	TIndexIterator m_indexIter; // The index that looks up the underlying container
};

}
