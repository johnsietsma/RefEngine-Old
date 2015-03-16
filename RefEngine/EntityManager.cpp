#include "EntityManager.h"

// Start the entity id count at 0
std::atomic<uint> reng::EntityManager::CurrentEntityId = 0;
