#pragma once

#include "component/DebugComponent.h"

#include "entity/ComponentDatabase.h"
#include "entity/ComponentHandle.h"

#include <algorithm>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace reng {

typedef size_t EntityId;


class Entity
{
public:
    Entity(EntityId id, const char* name, ComponentDatabase* a_pDatabase) :
		m_id(id),
		m_name(name),
        m_pDatabase(a_pDatabase)
    {}

	EntityId GetId() const { return m_id; }
	const std::string& GetName() const { return m_name;  }

	bool HasDebugComponents() const { return m_debugTypeIds.size() > 0; }

    template<typename T>
    ComponentHandle EmplaceComponent() 
    {
        if (!m_pDatabase->HasComponentContainer<T>()) m_pDatabase->AddComponentContainer<T>();
        auto& compContainer = m_pDatabase->GetComponentContainer<T>();
        ComponentId id = compContainer.EmplaceComponent();
        ComponentTypeId typeId = Component::GetTypeId<T>();
        auto handle = ComponentHandle( typeId, id );
        m_componentHandles.push_back(handle);
        
        if (std::is_base_of<DebugComponent,T>::value) {
            AddDebugType<T>( typeId );
        }
        
        return handle;
    }

    template<typename T, class ...TArgs>
    ComponentHandle EmplaceComponent(TArgs... args)
    {
        if (!m_pDatabase->HasComponentContainer<T>()) m_pDatabase->AddComponentContainer<T>();
        auto& compContainer = m_pDatabase->GetComponentContainer<T>();
        ComponentId id = compContainer.EmplaceComponent(args...);
		ComponentTypeId typeId = Component::GetTypeId<T>();
        auto handle = ComponentHandle( typeId, id );
		m_componentHandles.push_back(handle);

		if (std::is_base_of<DebugComponent,T>::value) {
			AddDebugType<T>( typeId );
		}

		return handle;
    }

	void DrawDebugUI( ComponentDatabase& database )
	{
		for (const auto& componentHandle : m_componentHandles)
		{
			if (IsDebugType(componentHandle.typeId)) {
				auto& componentContainer = database.GetComponentContainer(componentHandle.typeId);
				void* pComponent = componentContainer.GetComponentPointer(componentHandle.id);
				dynamic_cast<DebugComponent*>(static_cast<DebugComponent*>(pComponent))->DrawDebugUI(componentHandle.id);
			}
		}
	}

private:
	template<typename T>
	void AddDebugType( ComponentTypeId typeId )
	{
		if (std::find(m_debugTypeIds.begin(), m_debugTypeIds.end(), typeId) == m_debugTypeIds.end())
		{
			m_debugTypeIds.push_back(typeId);
		}
	}

	bool IsDebugType(ComponentTypeId typeId)
	{
		return std::find(m_debugTypeIds.begin(), m_debugTypeIds.end(), typeId) != m_debugTypeIds.end();
	}


	EntityId m_id;
	std::string m_name;
	std::vector<ComponentHandle> m_componentHandles;
	std::vector<ComponentTypeId> m_debugTypeIds; // Keep track of debug types we own.

    // The database that contains the components from this Entity.
    ComponentDatabase* m_pDatabase;
};

}
