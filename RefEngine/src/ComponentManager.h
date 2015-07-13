#pragma once

#include "ComponentContainer.h"
#include "StronglyTyped.h"
#include "types.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace reng {

using namespace std;

// fwd decls
STRONG_TYPE_DEF(uint,EntityId)

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
	ComponentManager();
	~ComponentManager(); // So unique_ptr has the complete type

	template<typename TComponent>
	ComponentContainer<TComponent>* GetComponentContainer()
	{
		const type_info& ti = typeid(TComponent);
		if (m_typeContainerMap.find(ti) == m_typeContainerMap.end()) {
			// Create the component container if it doesn't exist yet.
			m_typeContainerMap.emplace(ti, unique_ptr<IComponentContainer>(new ComponentContainer<TComponent>));
		}
		return m_typeContainerMap.at(ti)->AsTyped<TComponent>();
	}


private:
	size_t GetNumberOfComponentContainers() const;

	//! A map from type info to the container that holds that type.
	std::unordered_map< std::type_index, unique_ptr<IComponentContainer> > m_typeContainerMap;
};

}
