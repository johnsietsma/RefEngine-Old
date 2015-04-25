#pragma once

#include "Entity.h"
#include "pow2assert.h"


#include <algorithm>
#include <atomic>
#include <limits>
#include <vector>

namespace reng {


struct Entity
{
	EntityId m_entityId;
	// TODO: vector<EntityId> m_children;
};


/**
 * Manages the entities that are considered alive.
 * Each entity is represented by a uint, no assumptions are made about how it is used.
 * Lots of ideas implemented here are from: http://bitsquid.blogspot.com.au/2014/08/building-data-oriented-entity-system.html
 */
class EntityManager
{
public:
	EntityManager();

	size_t GetNumberOfEntites() const { return m_deadIndex; }
	EntityId Create();
	void Destroy(EntityId entityId);
	bool IsAlive(EntityId entityId);

private:
	std::vector<EntityId> m_entities; // TODO: Sort by heirarchy for top down transform updates.
	int m_deadIndex; // An index into m_entities that marks where the dead entities start. This index may point to end().
	bool m_isSorted = false;

	// Assume safety for a thread per EntityManager
	static std::atomic<uint> CurrentEntityId;

	// TODO: Unit tests!
};

}
