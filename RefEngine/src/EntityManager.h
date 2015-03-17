#pragma once

#include "pow2assert.h"
#include "StronglyTyped.h"
#include "types.h"

#include <algorithm>
#include <atomic>
#include <limits>
#include <vector>

namespace reng {

STRONG_TYPE(uint, EntityId, -1)

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
	EntityId Create() {
		uint newId = CurrentEntityId++;
		POW2_ASSERT(std::numeric_limits<uint>::max() != CurrentEntityId); // Check for overuns
		m_entities.push_back(newId); // Store the new id
		m_deadIndex++; // Keep track of where the dead entites start
		m_isSorted = false; // Mark the sorted as dirty
		return newId;
	}

	void Destroy( EntityId entityId )
	{
		std::vector<EntityId>::iterator it = find(m_entities.begin(), m_entities.begin() + m_deadIndex, entityId);
		if (it != m_entities.end()) {
			// Swawp the last live entity with the one being destroyed. Then we can just decrement the dead index to destroy it.
			std::iter_swap(it, m_entities.begin() + m_deadIndex - 1);
			m_deadIndex--;
			m_isSorted = false;
		}
		else {
			POW2_ASSERT_FAIL("Entity &d doesn't exist and can't be destroyed", entityId.Value());
		}
	}

	bool IsAlive(EntityId entityId) {
		if (!m_isSorted) {
			// Assume that the alive check is commonly called, only sort when needed, then use fast binary search
			std::sort(m_entities.begin(), m_entities.begin() + m_deadIndex );
			m_isSorted = true;
		}

		std::vector<EntityId>::iterator foundEntity = std::lower_bound(m_entities.begin(), m_entities.begin() + m_deadIndex, entityId);
		return foundEntity != m_entities.end();
	}

private:
	std::vector<EntityId> m_entities; // TODO: Sort by heirarchy for top down transform updates.
	int m_deadIndex; // An index into m_entities that marks where the dead entities start. This index may point to end().
	bool m_isSorted = false;

	// Assume safety for a thread per EntityManager
	static std::atomic<uint> CurrentEntityId;

	// TODO: Unit tests!
};

}
