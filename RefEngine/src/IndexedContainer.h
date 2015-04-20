#pragma once

#include "pow2assert.h"
#include "types.h"

#include <map>

template<typename TElement>
class IndexedContainerTyped;

//! The base class for IndexedContainers. 
/*!
Used as a simple holder for storage in user's homogenous containers.
*/
class IndexedContainer {
public:
	//! Return a derived instance of IndexedContainer that stores a particular type.
	template<typename T>
	IndexedContainerTyped<T>* AsTyped() {
		return static_cast<IndexedContainerTyped<T>*>(this);
	}
};


//! A templated indexed container.
/*!
IndexedContainers store a mapping between indexes and multiple elements in the container.
Users can get a list individual element indexes that are associated with an id or
to get elements by index.

A use case is Entities that are associated with Components. A Component can be stored
in an IndexedContainer and associated with a specific Entity. Then either all Components
of a particular type can be operated on, or Components of a particular Entity retrieved by index.

This also give better CPU cache performance as elements are stored in contiguous memory.

*/
template<typename TElement>
class IndexedContainerTyped : public IndexedContainer {
public:
	int Size() const { return elements.size();  }

	//! Get an element at an index.
	TElement& GetByIndex(uint index) {
		return elements[index];
	}

	TElement& GetFirst(uint assocId) {
		int index = elementIndexMap[assocId].at(0);
		return elements[index];
	}

	std::vector<TElement>& GetAll() {
		return elements;
	}

	//! Get all the elements associated with the given id.
	std::vector<uint>& GetIndexes(uint assocId) {
		return elementIndexMap[assocId];
	}

	//! Make a new element, store it and return a reference to it.
	//! Takes an index to associate with the element and arguments used to contruct it.
	template< class... Args >
	TElement& Add( uint assocId, Args&&... args )
	{
		// Add a new element to the templated container map
		elements.emplace_back(args...);

		// Store the associated index of the element for this element
		size_t componentIndex = elements.size() - 1;
		elementIndexMap[assocId].push_back(componentIndex);

		return elements.back();
	}

	//! Remove an element
	void Remove(uint assocId)
	{
		// Get the component to remove
		auto elementIndexes = elementIndexMap.at(assocId);
		POW2_ASSERT(elementIndexes.size() > 0);
		uint componentIndex = elementIndexes.back();

		// Remove the associated index
		elementIndexes.pop_back();

		POW2_ASSERT(elements.size() > componentIndex);
		elements.erase(elements.begin() + componentIndex);
	}

private:
	std::vector<TElement> elements;

	//! A map from indexes to the index of elements associated with it.
	std::map<uint, std::vector<uint>> elementIndexMap;
};
