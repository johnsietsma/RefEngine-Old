#pragma once

#include "StronglyTyped.h"
#include "types.h"

#include <map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <vector>

namespace reng {

using namespace std;

// fwd decls
STRONG_TYPE_DEF(uint,EntityId)
class Renderable;
class Processor;
class SpinController;
class GameTime;
class Transform;


//! A generic component container.
/*!
	This class doesn't hold components, it provides a non-templated base class
	for subclasses which will hold the components.
	It doesn't provide a way to map between entities and the components that 
	are stored within the container.
*/
class EntityComponentContainer {
public:
	//! A map from EntityIds to the index of components associated with it.
	std::map<EntityId, std::vector<int>> entityIndexMap;
};


//! A templated component container.
/*! 
	Extends EntityComponentContainer and provides type specific storage for
	components.
*/
template<typename TComponent>
class EntityComponentContainerT : public EntityComponentContainer {
public:
	std::vector<TComponent> components;
};


struct SpinComponent {
	Transform* pTransform;
	GameTime* pTime;
};


//! ComponentManager stores components of specific types.
/*!
	An entity is made up of components. The ComponentManager stores each
	type of component in contiguous memory, while still allowing components
	to be looked up by entity. 
	This gives better cache performance when larger numbers of homogenous
	components are used.
	Components are stored by value and returned by reference. So any
	modified components must be explicitly set.
	Entities aren't stored explicitly, instead a mapping is maintained between
	EntityId's and their components.
*/
class ComponentManager
{
public:
	ComponentManager();

	//! Get the number of components of a particluar type.
	template<typename TComponent>
	size_t GetNumberOfComponents() const {
		size_t key = GetKey<TComponent>();
		if (Contains<TComponent>()) { return GetEntityComponentContainerT<TComponent>( m_componentsMap.at(key) )->components.size(); };
		return 0;
	}

	//! Test whether a component of a particular type is being stored.
	template<typename TComponent>
	bool Contains() const {
		size_t key = GetKey<TComponent>();
		return m_componentsMap.find(key) != m_componentsMap.end();
	}

	template<typename T>
	void RegisterProcessor();

	// Process all the objects of a certain type
	template<typename TComponent>
	void Process(std::vector<TComponent> processObjects);

	//! Add a component of a particular type that is associated with the given entity.
	template<typename TComponent>
	void AddComponent(const EntityId& entityId)
	{
		EntityComponentContainerT<TComponent>* componentContainer = GetOrCreateComponentContainer<TComponent>();

		TComponent component;

		// Add the component to the templated container map
		componentContainer->components.emplace_back(component);

		// Store the index of the component for this entity
		size_t componentIndex = componentContainer->components.size() - 1;
		componentContainer->entityIndexMap[entityId].emplace_back(componentIndex);
	}

	//! Removes a component of type TComponent.
	/*!
		This will remove the last added component.
	*/
	template<typename TComponent>
	void RemoveComponent(const EntityId& entityId)
	{
		EntityComponentContainerT<TComponent>* componentContainer = GetComponentContainer<TComponent>();
		vector<TComponent>& components = componentContainer->components;

		// Remove the component
		components.pop_back();

		// And its index
		componentContainer->entityIndexMap[entityId].pop_back();
	}


private:
	template<typename TComponent>
	size_t GetKey() const {
		return typeid(TComponent).hash_code();
	}

	template<typename TComponent>
	EntityComponentContainerT<TComponent>* GetEntityComponentContainerT(EntityComponentContainer* container)
	{
		return reinterpret_cast<EntityComponentContainerT<TComponent>*>(container);
	}

	template<typename TComponent>
	const EntityComponentContainerT<TComponent>* GetEntityComponentContainerT(const EntityComponentContainer* container) const
	{
		return reinterpret_cast<const EntityComponentContainerT<TComponent>*>(container);
	}

	template<typename TComponent>
	EntityComponentContainerT<TComponent>* GetComponentContainer()
	{
		size_t key = GetKey<TComponent>();
		return GetEntityComponentContainerT<TComponent>(m_componentsMap[key]); // Will throw if doesn't exist
	}

	template<typename TComponent>
	EntityComponentContainerT<TComponent>* GetOrCreateComponentContainer()
	{
		size_t key = GetKey<TComponent>();

		if ( !Contains<TComponent>() ) {
			m_componentsMap[key] = new EntityComponentContainerT<TComponent>();
		}

		return GetEntityComponentContainerT<TComponent>(m_componentsMap[key]);
	}

	// A map of types to processors that can process objects of that type
	std::map<size_t,Processor*> m_processorMap;

	// A map of types to all the components of that type.
	// They are stored in a generic base class, so the derived class can hold a std::vector of a certain type.
	std::map<size_t, EntityComponentContainer*> m_componentsMap;


};

}
