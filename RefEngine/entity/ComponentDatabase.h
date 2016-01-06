#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"
#include "utils/pow2assert.h"

#include <unordered_map>

namespace reng {


// A dataabse that maps ComponentTypeIds to ComponentContainers
class ComponentDatabase
{
public:
    template<typename T>
    bool HasComponentContainer() {
        const auto& typeId = Component::GetTypeId<T>();
        return HasComponentContainer(typeId);
    }

    bool HasComponentContainer( ComponentTypeId typeId ) {
        return m_componentMap.count(typeId) > 0;
    }

    template<typename T>
    ComponentContainer<T>& GetComponentContainer() {
        const auto& typeId = Component::GetTypeId<T>();
        POW2_ASSERT_MSG(HasComponentContainer<T>(), "Component type has not been added");
        return *static_cast<ComponentContainer<T>*>(m_componentMap[typeId].get());
    }

    IComponentContainer& GetComponentContainer( ComponentTypeId typeId ) {
        return *m_componentMap[typeId].get();
    }

    template<typename T>
    ComponentTypeId AddComponentContainer() {
        const auto& typeId = Component::GetTypeId<T>();
        POW2_ASSERT_MSG(!HasComponentContainer<T>(), "ComponentType has already been added");
        m_componentMap.emplace(typeId, std::make_unique<ComponentContainer<T>>());
        return typeId;
    }

private:
    // Map a component type to a component container
    std::unordered_map< ComponentTypeId, std::unique_ptr<IComponentContainer> > m_componentMap;
};


}