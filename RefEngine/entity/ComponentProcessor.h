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
template<typename T>
using ComponentProcessorFunction = std::function<void(double,ComponentContainer<T>&) >;

// Base class for component processing. Allows generic storage of processors.
class IComponentProcessor
{
public:
    virtual void Process( double deltaTime, IComponentContainer& container ) = 0;
};

// A component processor that is responsible for updating components.
template<typename T>
class ComponentProcessor : public IComponentProcessor
{
public:
    ComponentProcessor(ComponentProcessorFunction<T> a_processorFuntion) :
        m_processorFunction(a_processorFuntion)
    {}

    void Process( double deltaTime, IComponentContainer& baseContainer ) override
    {
        m_processorFunction(deltaTime, static_cast<ComponentContainer<T>&>(baseContainer));
    }

private:
    ComponentProcessorFunction<T> m_processorFunction;
};

// Manages component processors.
// Maps ComponentTypeIds to component processors and will process them all
//   with ComponentContainers from the ComponentDatabase.
class ComponentProcessorManager
{
public:
    template<typename T>
    void RegisterComponentProcessor(ComponentProcessorFunction<T> processorFunction)
    {
        const auto& typeId = Component::GetTypeId<T>();
        m_processors.emplace(typeId, std::make_unique< ComponentProcessor<T> >(processorFunction));
    }

    void Process(double deltaTime, ComponentDatabase& database);
    
private:
    std::unordered_map<ComponentTypeId, std::unique_ptr<IComponentProcessor>> m_processors;

};

}