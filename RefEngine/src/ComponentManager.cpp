#include "ComponentManager.h"

using namespace reng;

// Need these in the cpp so that unique_ptr know how to delete component manager
ComponentManager::ComponentManager() {}
ComponentManager::~ComponentManager() {}

size_t ComponentManager::GetNumberOfComponentContainers() const
{
	return m_typeContainerMap.size();
}
