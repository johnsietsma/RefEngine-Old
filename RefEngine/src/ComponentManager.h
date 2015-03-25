#pragma once

#include "StronglyTyped.h"
#include "types.h"

#include <map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <vector>

namespace reng {

STRONG_TYPE_DEF(uint,EntityId)
//class ComponentContainer;
class Renderable;
class Processor;
class SpinController;
class GameTime;
class Transform;


// A non-templated base class for component containers
class ComponentContainer {
public:
	// A map from EntityIds to the index of components it contains.
	std::map<EntityId, std::vector<int>> entityIndexMap;
};

template<typename TComponent>
class ComponentContainerT : public ComponentContainer {
public:
	std::vector<TComponent> components;
};


struct SpinComponent {
	Transform* pTransform;
	GameTime* pTime;
};


class ComponentManager
{
public:
	ComponentManager();

	template<typename T>
	void RegisterProcessor();

	// Process all the objects of a certain type
	template<typename TComponent>
	void Process(std::vector<TComponent> processObjects);

	template<typename TComponent>
	void AddComponent(const EntityId& entityId, const TComponent& component)
	{
		ComponentContainerT<TComponent>* componentContainer = GetOrCreateComponentContainer(component);

		// Add the component to the templated container map
		componentContainer->components.emplace_back(component);

		// Store the idnex of the component for this entity
		componentContainer->entityIndexMap[entityId].push_back(componentContainer->components.size() - 1);
	}

private:
	template<typename TComponent>
	ComponentContainerT<TComponent>* GetOrCreateComponentContainer(const TComponent& component)
	{
		size_t key = typeid(TComponent).hash_code();

		if (m_componentsMap.find(key) == m_componentsMap.end()) {
			m_componentsMap[key] = new ComponentContainerT<TComponent>();
		}

		return reinterpret_cast<ComponentContainerT<TComponent>*>(m_componentsMap[key]);
	}

	// A map of types to processors that can process objects of that type
	std::map<size_t,Processor*> m_processorMap;

	// A map of types to all the components of that type.
	// They are stored in a generic base class, so the derived class can hold a std::vector of a certain type.
	std::map<size_t,ComponentContainer*> m_componentsMap;


};

}
