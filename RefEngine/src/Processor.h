#pragma once

#include "ComponentManager.h"

#include <vector>

namespace reng {

	template<typename TComponent, typename... TArgs>
class Processor
{
public:
	void Process( ComponentManager& componentManager, TArgs... args )
	{
		// Use the first type as the main component type. Get all it's EntityIds.
		auto componentContainer = componentManager.GetComponentContainer<TComponent>();
		auto& entityIds = componentContainer->GetEntityIds();
		DoProcess(entityIds, componentManager, args...);
	}

private:
	virtual void DoProcess(
		const std::vector<EntityId>& entityIds, // The entity ids of the processed components
		ComponentManager& componentManager, // Provides access to components
		TArgs&... args // user-defined args
		) = 0;
};

}
