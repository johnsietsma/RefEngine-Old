#include "Entity.h"

#include "ComponentManager.h"
#include "EntityManager.h"

using namespace reng;

Entity::Entity(std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<EntityManager> entityManager) :
	m_entityId(entityManager->CreateId()),
	m_componentManager(componentManager),
	m_entityManager(entityManager)
{
}

Entity::~Entity()
{
	m_entityManager->Destroy(shared_from_this());
}
