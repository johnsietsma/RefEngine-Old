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
using ComponentContainerProcessorFunction = std::function<void(TArg,ComponentContainer<T>&, ComponentDatabase&) >;

// Base class for component processing. Allows generic storage of processors.
class IComponentContainerProcessor
{
public:
    virtual void Process( void* arg, IComponentContainer& container, ComponentDatabase& database ) = 0;
};

// A component processor that is responsible for updating components.
template<typename T, typename TArg>
class ComponentContainerProcessor : public IComponentContainerProcessor
{
public:
    ComponentContainerProcessor(ComponentContainerProcessorFunction<T,TArg> a_processorFuntion) :
        m_processorFunction(a_processorFuntion)
    {}

    void Process( void* arg, IComponentContainer& baseContainer, ComponentDatabase& database ) override
    {
        m_processorFunction(*static_cast<TArg*>(arg), static_cast<ComponentContainer<T>&>(baseContainer), database);
    }

private:
    ComponentContainerProcessorFunction<T,TArg> m_processorFunction;
};

// Manages component processors.
// Maps ComponentTypeIds to component processors and will process them all
//   with ComponentContainers from the ComponentDatabase.
class ComponentContainerProcessorManager
{
public:
    template<typename T, typename TArg>
    void AddComponentProcessor(ComponentContainerProcessorFunction<T, TArg> processorFunction)
    {
        const auto& typeId = Component::GetTypeId<T>();
        m_processors.emplace(typeId, std::make_unique< ComponentContainerProcessor<T, TArg> >(processorFunction));
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
            processor->Process(&arg, componentContainer, database);
        }
    }
    
private:
    std::unordered_map<ComponentTypeId, std::unique_ptr<IComponentContainerProcessor>> m_processors;

};

}