#include "ComponentManager.h"
#include "pow2assert.h"
#include "Processor.h"
#include "GameTime.h"
#include "Transform.h"

#include <typeinfo>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace reng {
template<typename TComponent>
class ComponentContainer {
	std::vector<TComponent> components;
};


class SpinProcessor : public Processor
{
public:

	void Process(std::vector<SpinComponent>& spinComponents) {
		for (SpinComponent& spin : spinComponents) {
			spin.pTransform->SetTransform( glm::rotate<float>(spin.pTransform->GetTransform(), 10 * spin.pTime->deltaTime, glm::vec3(0, 1.f, 0)) );
		}
	}
};
}


using namespace reng;


ComponentManager::ComponentManager()
{
	RegisterProcessor<SpinProcessor>();
}

template<typename TComponent>
void ComponentManager::AddComponent(const TComponent& component)
{
	size_t key = typeid(TComponent).hash_code();
	if( m_componentsMap.find(key) == m_componentsMap.end() ) {
		m_componentsMap[key] = new ComponentContainer<TComponent>();
	}
    dynamic_cast<ComponentContainer<TComponent>>(m_componentsMap[key]).components.emplace_back(component);
}


template<typename T>
void ComponentManager::RegisterProcessor()
{
	size_t key = typeid(T).hash_code();
	POW2_ASSERT(m_processorMap.find(key) == m_processorMap.end());
	m_processorMap[key] = new T();
}

template<typename T>
void ComponentManager::Process(std::vector<T> processObjects)
{
	size_t key = typeid(T).hash_code();
	POW2_ASSERT(m_processorMap.find(key) != m_processorMap.end());
//	m_processors[key]->Process(processObjects);
}
