#include "EntityManager.h"

#include "ComponentManager.h"
#include "Entity.h"

using namespace reng;


// Start the entity id count at 0
std::atomic<uint> reng::EntityManager::CurrentEntityId(0);

EntityManager::EntityManager() :
	EntityManager(new ComponentManager())
{}

EntityManager::EntityManager(ComponentManager* componentManager) :
	m_deadIndex(0),
	m_isSorted(true),
	m_componentManager(componentManager)
{

}

EntityId EntityManager::CreateId() {
	uint newId = CurrentEntityId++;
	POW2_ASSERT(std::numeric_limits<uint>::max() != CurrentEntityId); // Check for overuns
	m_entities.push_back(newId); // Store the new id
	m_deadIndex++; // Keep track of where the dead entites start
	m_isSorted = false; // Mark the sorted as dirty
	return newId;
}

std::shared_ptr<Entity> EntityManager::Create() {
	return std::make_shared<Entity>(m_componentManager, shared_from_this());
}

void EntityManager::Destroy(Entity* pEntity)
{
	std::vector<EntityId>::iterator it = find(m_entities.begin(), m_entities.begin() + m_deadIndex, pEntity->GetId());
	if (it != m_entities.end()) {
		// Swawp the last live entity with the one being destroyed. Then we can just decrement the dead index to destroy it.
		std::iter_swap(it, m_entities.begin() + m_deadIndex - 1);
		m_deadIndex--;
		m_isSorted = false;
	}
	else {
		POW2_ASSERT_FAIL("Entity &d doesn't exist and can't be destroyed", pEntity->GetId().Value());
	}
}

bool EntityManager::IsAlive(Entity* pEntity) {
	if (!m_isSorted) {
		// Assume that the alive check is commonly called, only sort when needed, then use fast binary search
		std::sort(m_entities.begin(), m_entities.begin() + m_deadIndex);
		m_isSorted = true;
	}

	std::vector<EntityId>::iterator foundEntity = std::lower_bound(m_entities.begin(), m_entities.begin() + m_deadIndex, pEntity->GetId());
	return foundEntity != m_entities.end();
}