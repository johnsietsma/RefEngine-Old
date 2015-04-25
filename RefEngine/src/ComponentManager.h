#pragma once

//#include "ComponentContainer.h"
#include "Processor.h"
#include "StronglyTyped.h"
#include "types.h"

#include <map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <vector>

namespace reng {

using namespace std;

// fwd decls
STRONG_TYPE_DEF(uint,EntityId)
class Renderable;
class SpinController;
class GameTime;

//! ComponentManager stores components of specific types.
/*!
	An entity is made up of components. The ComponentManager stores each
	type of component in contiguous memory, while still allowing components
	to be looked up by entity. 
	Entities aren't stored explicitly, instead a mapping is maintained between
	EntityId's and their components.
*/
class ComponentManager
{
public:
	ComponentManager() {};

	/*template<typename T>
	void RegisterProcessor( std::function<void(T,void*) ){
		type_info key = typeid(T);
		POW2_ASSERT(m_processorMap.find(key) == m_processorMap.end());
		m_processorMap[key] = new T();
	}*/


	// Process all the objects of a certain type
	//template<typename TComponent>
	/*void Process(std::vector<int> processObjects)
	{

	}*/

private:
	// A map of types to processors that can process objects of that type
	//std::map<type_info,Processor*> m_processorMap;

	//ComponentContainerTyped<int> m_componentContainer;
	//Processor<int, bool&> m_processor;

};

}
