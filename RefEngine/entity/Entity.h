#pragma once

#include "entity/ComponentDatabase.h"
#include "entity/ComponentHandle.h"
#include "entity/ComponentProcessor.h"

#include <typeindex>
#include <unordered_map>

namespace reng {

class Entity
{
public:
    Entity(ComponentDatabase* a_pDatabase) :
        m_pDatabase(a_pDatabase)
    {}

    template<typename T>
    ComponentHandle<T> EmplaceComponent() 
    {
        return EmplaceComponent<T,void>();
    }

    template<typename T, class ...TArgs>
    ComponentHandle<T> EmplaceComponent(TArgs... args)
    {
        if (!m_pDatabase->HasComponentContainer<T>()) m_pDatabase->AddComponentContainer<T>();
        auto& compContainer = m_pDatabase->GetComponentContainer<T>();
        ComponentId id = compContainer.EmplaceComponent(args...);
        return ComponentHandle<T>( compContainer, id );
    }

private:
    // A map of the components associated with this Entity.
    std::unordered_map< ComponentTypeId, std::unique_ptr<ComponentId> > m_componentMap;

    // The database that contains the components from this Entity.
    ComponentDatabase* m_pDatabase;
};

}
