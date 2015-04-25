#pragma once

#include "Entity.h"
#include "pow2assert.h"
#include "types.h"

#include <map>
#include <stdexcept>

namespace reng {

template<typename TComponent>
class ComponentContainerTyped;

//! The base class for ComponentContainers. 
/*!
This provides a unified type for ComponentContainers.
*/
class ComponentContainer {
public:
	//! Return a derived instance of IndexedContainer that stores a particular type.
	template<typename T>
	ComponentContainerTyped<T>* AsTyped() {
		return static_cast<ComponentContainerTyped<T>*>(this);
	}
};


//! A templated component container.
/*!
ComponentContainers provide storage for a single component type. 
Their main purposes are:
	* To provide a way to get the EntityId a component belongs to.
	* To provide a way to get the all components associated with a particular EntityId.
	* To provide access to all the components.
	* To store the components in contiguous storage for good CPU cache performance.
*/
template<typename TComponent>
class ComponentContainerTyped : public ComponentContainer {
public:
	//! Get all the components stored in this container.
	std::vector<TComponent>& GetComponents() {
		return components;
	}

	//! Returns the first component associated with an entity.
	//! Throws an out_of_range_exception if no components are associated with the entity.
	TComponent& GetFirstComponent(EntityId entityId) {
		if (entityId.Value() >= elementIndexMap.size()) throw std::out_of_range("entityId");
		int index = elementIndexMap[entityId].at(0);
		return components[index];
	}

	//! Get all the components associated with the given entity.
	std::vector<uint>& GetComponentIndexes(EntityId entityId) {
		return elementIndexMap[entityId];
	}


	//! Returns the EntityId associated with the component at the given index.
	EntityId GetEntityId(uint componentIndex) {
		return entityIds[componentIndex];
	}

	//! Make a new element, store it and return a reference to it.
	//! Takes an index to associate with the element and arguments used to contruct it.
	template< class... Args >
	TComponent& Add( EntityId entityId, Args&&... args )
	{
		// Add a new element to the templated container map
		components.emplace_back(args...);

		// Store the associated entity
		entityIds.push_back(entityId);

		// Store the associated index of the element for this element
		size_t componentIndex = components.size() - 1;
		elementIndexMap[entityId].push_back(componentIndex);

		return components.back();
	}

	//! Remove an element
	void Remove(EntityId entityId)
	{
		// Get the component to remove
		auto elementIndexes = elementIndexMap.at(entityId);
		POW2_ASSERT(elementIndexes.size() > 0);
		uint componentIndex = elementIndexes.back();

		// Remove the associated index
		elementIndexes.pop_back();

		// Remove the component
		POW2_ASSERT(components.size() > componentIndex);
		components.erase(components.begin() + componentIndex);

		// Remove the associcated entity id
		entityIds.erase(entityIds.begin() + componentIndex);
	}

private:
	std::vector<TComponent> components; // All the components
	std::vector<EntityId> entityIds;  // All the component's EntityIds. Indexes provide a one to one mapping from components.

	//! A map from indexes to the index of components associated with it.
	std::map<EntityId, std::vector<uint>> elementIndexMap;
};

}