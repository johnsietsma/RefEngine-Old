#pragma once

#include <map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <vector>

namespace reng {

class Renderable;
class Processor;
class SpinController;
class GameTime;
class Transform;

// A non-templated base class for component containers
class ComponentContainerBase {};

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
	void AddComponent(const TComponent& component);

private:
	// A map of types to processors that can process objects of that type
	std::map<size_t,Processor*> m_processorMap;

	// A map of types to all the components of that type.
	// They are stored in a generic base class, so the derived class can hold a std::vector of a certain type.
	std::map<size_t,ComponentContainerBase> m_componentsMap;

	std::vector<Transform> m_transformComponents;
	std::vector<SpinComponent> m_spinComponents;
};

}
