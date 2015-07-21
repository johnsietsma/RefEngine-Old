#pragma once

#include "StronglyTyped.h"
#include "types.h"

#include "utils/pow2assert.h"

#include <functional>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

namespace reng {

// fwd decls
STRONG_TYPE_DEF(uint, EntityId)

template<typename TComponent>
class ComponentContainer;


//! The base class for ComponentContainers.
/*!
This provides a unified type for ComponentContainers.
*/
class IComponentContainer {
public:
	virtual ~IComponentContainer() = default;

	//! Return a derived instance of IndexedContainer that stores a particular type.
	template<typename T>
	ComponentContainer<T>* AsTyped() {
		return dynamic_cast<ComponentContainer<T>*>(this);
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
class ComponentContainer : public IComponentContainer {
public:
	typedef typename std::vector<TComponent>::iterator component_iterator;
	typedef typename std::vector<EntityId>::iterator entityid_iterator;

	virtual ~ComponentContainer() = default;

	bool Has(EntityId entityId)
	{
		auto findIter = m_elementIndexMap.find(entityId);
		return findIter != m_elementIndexMap.end();
	}

	//! Get all the components stored in this container.
	std::vector<TComponent>& GetAll()
	{
		return m_components;
	}

	//! Get the component associated with the given entity.
	TComponent& Get(EntityId entityId)
	{
		uint componentIndex = m_elementIndexMap.at(entityId);
		return m_components[componentIndex];
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

	component_iterator begin() { return m_components.begin(); }
	component_iterator end() { return m_components.end(); }

	//! Make a new element, store it and return a reference to it.
	//! Takes an index to associate with the element and arguments used to contruct it.
	TComponent& Add( EntityId entityId, TComponent& component )
	{
		return DoAdd(entityId, [&, component]() {
			// Add a new element to the templated container map
			m_components.push_back(component);
		});
	}

	template< class... Args >
	TComponent& Emplace(EntityId entityId, Args&&... args)
	{
		return DoAdd(entityId, [&, args...]() {
			// Emplace a new element to the templated container map
			m_components.emplace_back(args...);
		});
	}

	//! Remove an element
	void Remove(EntityId entityId)
	{
		// Remove the entity to index mapping
		uint componentIndex = m_elementIndexMap.at(entityId);
		m_elementIndexMap.erase(entityId);

		// Remove the component
		POW2_ASSERT(m_components.size() > componentIndex);
		m_components.erase(m_components.begin() + componentIndex);

		// Remove the associcated entity id
		m_entityIds.erase(m_entityIds.begin() + componentIndex);
	}

private:
	//! Make a new element, store it and return a reference to it.
	TComponent& DoAdd(EntityId entityId, std::function<void()> addFunc)
	{
		if (m_elementIndexMap.find(entityId) != m_elementIndexMap.end()) { throw std::invalid_argument("EntityId has already been added to the container."); }

		// Add a new element to the templated container map
		addFunc();

		// Store the associated entity
		m_entityIds.push_back(entityId);

		// Store the associated index of the element for this element
		size_t componentIndex = m_components.size() - 1;
		m_elementIndexMap[entityId] = componentIndex;

		return m_components.back();
	}

	std::vector<TComponent> m_components; // All the components
	std::vector<EntityId> m_entityIds;  // All the component's EntityIds. Indexes provide a one to one mapping from components.

	//! A map from indexes to the index of components associated with it.
	std::map< EntityId, uint > m_elementIndexMap;
};


}
