#pragma once

#include "Entity.h"
#include "IndexedContainer.h"
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
ComponentContainers provide storage for components of a single type.
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
	std::vector<TComponent>& GetComponents()
	{
		return m_components;
	}

	//! Get all the components associated with the given entity.
	std::vector<uint>& GetComponentIndexes(EntityId entityId)
	{
		return m_elementIndexMap[entityId];
	}

	//! Returns the EntityId associated with the component at the given index.
	EntityId GetEntityId(uint componentIndex) {
		return m_entityIds[componentIndex];
	}

	//! Return all the EntityIds that the components belong to.
	const std::vector<EntityId>& GetEntityIds() const
	{
		return m_entityIds;
	}

	//! Get a container that maps EntityIds to components.
	// This container can be iterated through in sequential order, even if the components
	// aren't sequential.
	IndexedContainer<TComponent> GetIndexedContainer(const std::vector<EntityId>& entityIds)
	{
		std::vector<uint> indexes;
		indexes.reserve(entityIds.size());

		for (uint i = 0; i < entityIds.size(); i++)
		{
			const EntityId id = entityIds[i];
			const std::vector<uint> entityIndexes = m_elementIndexMap[id];
			POW2_ASSERT_MSG(entityIndexes.size() > 0, "No entities with that id exist in this container.");
			POW2_ASSERT_MSG(entityIndexes.size() == 1, "Only one component type per entity supported in IndexedContainer.");
			indexes.push_back(entityIndexes.front());
		}
		return IndexedContainer<TComponent>(indexes, m_components);
	}

	//! Make a new element, store it and return a reference to it.
	//! Takes an index to associate with the element and arguments used to contruct it.
	template< class... Args >
	TComponent& Add( EntityId entityId, Args&&... args )
	{
		// Add a new element to the templated container map
		m_components.emplace_back(args...);

		// Store the associated entity
		m_entityIds.push_back(entityId);

		// Store the associated index of the element for this element
		size_t componentIndex = m_components.size() - 1;
		m_elementIndexMap[entityId].push_back(componentIndex);

		return m_components.back();
	}

	//! Remove an element
	void Remove(EntityId entityId)
	{
		// Get the component to remove
		auto elementIndexes = m_elementIndexMap.at(entityId);
		POW2_ASSERT(elementIndexes.size() > 0);
		uint componentIndex = elementIndexes.back();

		// Remove the associated index
		elementIndexes.pop_back();

		// Remove the component
		POW2_ASSERT(m_components.size() > componentIndex);
		m_components.erase(m_components.begin() + componentIndex);

		// Remove the associcated entity id
		m_entityIds.erase(m_entityIds.begin() + componentIndex);
	}

private:
	std::vector<TComponent> m_components; // All the components
	std::vector<EntityId> m_entityIds;  // All the component's EntityIds. Indexes provide a one to one mapping from components.

	//! A map from indexes to the index of components associated with it.
	std::map< EntityId, std::vector<uint> > m_elementIndexMap;
};

}
