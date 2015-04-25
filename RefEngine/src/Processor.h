#pragma once

#include <functional>
#include <vector>

namespace reng {

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