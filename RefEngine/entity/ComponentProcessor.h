#pragma once

#include "entity/ComponentContainer.h"

#include "make_unique.h"

#include <functional>
#include <memory>
#include <unordered_map>

namespace reng
{

class ComponentDatabase;

// Function which will update all the components in the container.
template<typename T, typename TArg>
using ComponentProcessorFunction = std::function<void(TArg,ComponentContainer<T>&) >;

// Base class for component processing. Allows generic storage of processors.
class IComponentProcessor
{
public:
    virtual void Process( void* arg, IComponentContainer& container ) = 0;
};

// A component processor that is responsible for updating components.
template<typename T, typename TArg>
class ComponentProcessor : public IComponentProcessor
{
public:
    ComponentProcessor(ComponentProcessorFunction<T,TArg> a_processorFuntion) :
        m_processorFunction(a_processorFuntion)
    {}

    void Process( void* arg, IComponentContainer& baseContainer ) override
    {
        m_processorFunction(*static_cast<TArg*>(arg), static_cast<ComponentContainer<T>&>(baseContainer));
    }

private:
    ComponentProcessorFunction<T,TArg> m_processorFunction;
};

// Manages component processors.
// Maps ComponentTypeIds to component processors and will process them all
//   with ComponentContainers from the ComponentDatabase.
class ComponentProcessorManager
{
public:
    template<typename T, typename TArg>
    void RegisterComponentProcessor(ComponentProcessorFunction<T, TArg> processorFunction)
    {
        const auto& typeId = Component::GetTypeId<T>();
        m_processors.emplace(typeId, std::make_unique< ComponentProcessor<T, TArg> >(processorFunction));
    }

    template<typename TArg>
    void Process(TArg arg, ComponentDatabase& database)
    {
        for (auto& processorPair : m_processors)
        {
            auto compTypeId = std::get<0>(processorPair);
            auto& processor = std::get<1>(processorPair);
            if (!database.HasComponentContainer(compTypeId)) continue;

            auto& componentContainer = database.GetComponentContainer(compTypeId);
            processor->Process(&arg, componentContainer);
        }
    }
    
private:
    std::unordered_map<ComponentTypeId, std::unique_ptr<IComponentProcessor>> m_processors;

};

}