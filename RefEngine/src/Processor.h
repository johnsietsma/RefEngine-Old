#pragma once

#include <vector>

namespace reng {

class Processor
{
public:
	template<typename T>
	void Process( std::vector<T> processObjects ) = 0;
};


}