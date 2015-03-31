#include "ComponentManager.h"

#include "EntityManager.h"
#include "GameTime.h"
#include "pow2assert.h"
#include "Processor.h"
#include "Transform.h"

#include <typeinfo>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace reng {

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
