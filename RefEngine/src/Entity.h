#pragma once

#include "StronglyTyped.h"
#include "types.h"

#include <memory>

namespace reng {

STRONG_TYPE(uint, EntityId, uint(-1))
class ComponentManager;
class EntityManager;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager);
	~Entity();

	EntityId GetId() const { return m_entityId; }

	template<typename TComponent>
	TComponent& AddComponent()
	{
		return m_componentManager->GetComponentContainer<TComponent>()->Add(m_entityId);
	}

	template<typename TComponent, typename... TArgs>
	TComponent& AddComponent(TArgs&&... args) 
	{
		return m_componentManager->GetComponentContainer<TComponent>()->Add<TArgs...>(m_entityId, std::forward<TArgs...>(args...));
	}

	template<typename TComponent>
	TComponent& GetComponent()
	{
		return m_componentManager->GetComponentContainer<TComponent>()->Get(m_entityId);
	}

private:
	EntityId m_entityId;
	std::shared_ptr<ComponentManager> m_componentManager;
	std::shared_ptr<EntityManager> m_entityManager;
};

}
