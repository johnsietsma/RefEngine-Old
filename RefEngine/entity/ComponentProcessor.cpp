#include "ComponentProcessor.h"

#include "entity/ComponentDatabase.h"

using namespace reng;

void ComponentProcessorManager::Process(double deltaTime, ComponentDatabase& database)
{
    for (auto& processorPair : m_processors)
    {
        auto compTypeId = std::get<0>(processorPair);
        auto& processor = std::get<1>(processorPair);
        if (!database.HasComponentContainer(compTypeId)) continue;

        auto& componentContainer = database.GetComponentContainer(compTypeId);
        processor->Process(deltaTime, componentContainer);
    }
}

