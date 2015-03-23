#include "ComponentManager.h"
#include "pow2assert.h"
#include "Processor.h"
#include "GameTime.h"
#include "Transform.h"

#include <typeinfo>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace reng;

class SpinProcessor : public Processor
{
public:

	void Process(std::vector<SpinComponent>& spinComponents) {
		for (SpinComponent& spin : spinComponents) {
			spin.pTransform->SetTransform( glm::rotate<float>(spin.pTransform->GetTransform(), 10 * spin.pTime->deltaTime, glm::vec3(0, 1.f, 0)) );
		}
	}
};


ComponentManager::ComponentManager()
{
	RegisterProcessor<SpinProcessor>();
}

void ComponentManager::AddComponent(const Transform& transform)
{
	m_transformComponents.emplace_back(transform);
}

void ComponentManager::AddComponent(const SpinComponent& spinComponent)
{
	m_spinComponents.emplace_back(spinComponent);
}


template<typename T>
void ComponentManager::RegisterProcessor()
{
	size_t key = typeid(T).hash_code();
	POW2_ASSERT(m_processors.find(key) == m_processors.end());
	m_processors[key] = new T();
}

template<typename T>
void ComponentManager::Process(std::vector<T> processObjects)
{
	size_t key = typeid(T).hash_code();
	POW2_ASSERT(m_processors.find(key) != m_processors.end());
//	m_processors[key]->Process(processObjects);
}
