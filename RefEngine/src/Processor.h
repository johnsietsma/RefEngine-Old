#pragma once

#include "ComponentManager.h"

#include <vector>

namespace reng {

template<typename TComponent>
class Processor
{
public:
	void Process( ComponentManager& componentManager )
	{
		// Use the first type as the main component type. Get all it's EntityIds.
		auto componentContainer = componentManager.GetComponentContainer<TComponent>();
		auto& entityIds = componentContainer->GetEntityIds();
		DoProcess(entityIds, componentManager);
	}

private:
	virtual void DoProcess(
		const std::vector<EntityId>& entityIds, // The entity ids of the processed components
		ComponentManager& componentManager // Provides access to components
		) = 0;
};

}
