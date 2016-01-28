#pragma once

#include "entity/ComponentDatabase.h"
#include "entity/ComponentHandle.h"

#include <string>
#include <typeindex>
#include <unordered_map>

namespace reng {

class Entity
{
public:
    Entity(const char* name, ComponentDatabase* a_pDatabase) :
		m_name(name),
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
	std::string m_name;


    // The database that contains the components from this Entity.
    ComponentDatabase* m_pDatabase;
};

}
