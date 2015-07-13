#pragma once

#include "ComponentManager.h"

#include <functional>
#include <vector>

namespace reng {


class IProcessor {
};

class ProcessorHolder
{
	void Process(reng::ComponentManager componentManager)
	{
		//auto iters = componentManager->GetIterators<Mesh*, Material*, Transform>();
		//m_pProcessor->Process(iters);
	}

	IProcessor m_pProcessor;

};

class ProcessorManager
{
public:
	void RegisterProcessor( IProcessor processor )
	{
		//m_processors.push_back(processor);
	}

	void Process( reng::ComponentManager componentManager )
	{
	}

private:
	std::vector<ProcessorHolder> m_processors;
};

template<typename T, typename TUserData>
class Processor
{
public:
	Processor( std::function<void(const std::vector<T>&, TUserData)> function ) :
		m_processor(function)
	{}

	void Process( std::vector<T>& data, TUserData userData )
	{
		m_processor(data, userData);
	}

private:
	std::function<void(const std::vector<T>&, TUserData)> m_processor;
};


}