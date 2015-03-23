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
class Time;
class Transform;

struct SpinComponent {
	Transform* pTransform;
	Time* pTime;
};




class ComponentManager
{
public:
	ComponentManager();

	template<typename T>
	void RegisterProcessor();

	// Process all the objects of a certain type
	template<typename T>
	void Process(std::vector<T> processObjects);

	void AddComponent(const Transform& transform);
	void AddComponent(const SpinComponent& spinComponent);

private:
	// Maps types to processors that can process objects of that type
	std::map<size_t,Processor*> m_processors;

	std::vector<Transform> m_transformComponents;
	std::vector<SpinComponent> m_spinComponents;
};

}
