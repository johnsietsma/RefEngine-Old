#pragma once

#include "ComponentContainer.h"
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
	size_t GetNumberOfComponentContainers() const 
	{
		return m_typeContainerMap.size();
	}

	//! Get the component container that holds the given type.
	template<typename TComponent>
	ComponentContainerTyped<TComponent>& GetComponentContainer()
	{
		const type_info& ti = typeid(TComponent);
		if (m_typeContainerMap.find(ti) == m_typeContainerMap.end()) {
			// Create the component container if it doesn't exist yet.
			m_typeContainerMap.emplace(ti, std::unique_ptr<ComponentContainerTyped<TComponent>>());
		}
		return m_typeContainerMap[ti]->AsTyped<TComponent>();
	}

	template<typename TComponent, typename... TComponents>
	ComponentContainerTyped<TComponent>& GetFirstComponentContainer()
	{
		return GetComponentContainer<TComponent>();
	}

	template<typename... TComponents>
	void Process(std::function<void(IndexedContainer<TComponents>...)> processFunction)
	{
		const std::vector<EntityId>& entityIds = GetFirstComponentContainer<TComponents...>().GetEntityIds();
		processFunction( 
			GetComponentContainer<TComponents>().GetIndexedContainer(entityIds)...
			);
	}

private:
	//! A map from type info to the container that holds that type/
	std::unordered_map<std::type_index, unique_ptr<ComponentContainer>> m_typeContainerMap;
};

}
