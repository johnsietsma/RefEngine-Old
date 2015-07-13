#pragma once

#include "ComponentManager.h"
#include "pow2assert.h"
#include "StronglyTyped.h"
#include "types.h"

#include <algorithm>
#include <atomic>
#include <limits>
#include <memory>
#include <vector>

namespace reng {

// fwd decls
STRONG_TYPE_DEF(uint, EntityId)
class Entity;

/**
 * Manages the entities that are considered alive.
 * Each entity is represented by a uint, no assumptions are made about how it is used.
 * Lots of ideas implemented here are from: http://bitsquid.blogspot.com.au/2014/08/building-data-oriented-entity-system.html
 */
class EntityManager : public std::enable_shared_from_this<EntityManager>
{
public:
	EntityManager();
	EntityManager( ComponentManager* componentManager );

	ComponentManager* GetComponentManager() { return m_componentManager.get();  }

	size_t GetNumberOfEntites() const { return m_deadIndex; }
	EntityId CreateId();
	std::shared_ptr<Entity> Create();
	void Destroy(Entity* pEntity);
	bool IsAlive(Entity* pEntity);

private:
	std::vector<EntityId> m_entities; // TODO: Sort by heirarchy for top down transform updates.
	int m_deadIndex; // An index into m_entities that marks where the dead entities start. This index may point to end().
	bool m_isSorted = false;

	std::shared_ptr<ComponentManager> m_componentManager;

	// Assume safety for a thread per EntityManager
	static std::atomic<uint> CurrentEntityId;
};

}
