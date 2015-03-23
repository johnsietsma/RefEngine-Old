#pragma once

namespace reng {

class Time
{
public:
	Time() :
		deltaTime(0),
		elapsedTime(0)
	{}

	float deltaTime;
	float elapsedTime;
};

}