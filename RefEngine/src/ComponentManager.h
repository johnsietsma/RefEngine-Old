#pragma once

#include "ComponentContainer.h"
#include "IndexedIterator.h"
#include "Processor.h"
#include "StronglyTyped.h"
#include "types.h"

#include <map>
#include <functional>
#include <memory>
#include <typeindex>
#include <vector>
#include <unordered_map>

namespace reng {

using namespace std;

// fwd decls
STRONG_TYPE_DEF(uint,EntityId)
class Renderable;
class SpinController;
class GameTime;

//! ComponentManager stores components of specific types.
/*!
	An entity is made up of components. The ComponentManager stores each
	type of component in contiguous memory, while still allowing components
	to be looked up by entity.
	Entities aren't stored explicitly, instead a mapping is maintained between
	EntityId's and their components.
*/
class ComponentManager
{
public:
	template<typename TComponent, typename... TArgs>
	TComponent& AddComponent(EntityId entityId, TArgs&&... args)
	{
		return GetOrCreateComponentContainer<TComponent>()->Add(entityId, args...);
	}

	template<typename TComponent>
	TComponent& GetComponent(EntityId entityId)
	{
		return GetComponentContainer<TComponent>()->Get(entityId);
	}

	template<typename TComponent>
	std::vector<TComponent>& GetComponents()
	{
		return GetComponentContainer<TComponent>()->GetAll();
	}

	template<typename... TComponents>
    void Process(std::function<void(ComponentIteratorPair<TComponents>...)> processFunction)
	{
		// Use the first type as the main component type. Get all it's EntityIds.
		const std::vector<EntityId>& entityIds = GetFirstComponentContainer<TComponents...>()->GetEntityIds();
		processFunction(
			GetOrCreateComponentContainer<TComponents>()->GetIterators(entityIds)...
			);
	}

private:
	size_t GetNumberOfComponentContainers() const
	{
		return m_typeContainerMap.size();
	}

	template<typename TComponent>
	ComponentContainer<TComponent>* GetComponentContainer()
	{
		const type_info& ti = typeid(TComponent);
		return m_typeContainerMap.at(ti)->AsTyped<TComponent>();
	}

	//! Get the component container that holds the given type.
	template<typename TComponent>
	ComponentContainer<TComponent>* GetOrCreateComponentContainer()
	{
		const type_info& ti = typeid(TComponent);
		if (m_typeContainerMap.find(ti) == m_typeContainerMap.end()) {
			// Create the component container if it doesn't exist yet.
			m_typeContainerMap.emplace(ti,unique_ptr<IComponentContainer>(new ComponentContainer<TComponent>));
		}
		return m_typeContainerMap[ti]->AsTyped<TComponent>();
	}

	//! Get the ComponentContainer of the first type in the template list
	template<typename TComponent, typename... TComponents>
	ComponentContainer<TComponent>* GetFirstComponentContainer()
	{
		return GetOrCreateComponentContainer<TComponent>();
	}

	//! A map from type info to the container that holds that type/
	std::unordered_map< std::type_index, unique_ptr<IComponentContainer> > m_typeContainerMap;
};

}
