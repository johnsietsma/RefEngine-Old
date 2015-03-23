#pragma once

namespace reng {

class GameTime
{
public:
	GameTime() :
		deltaTime(0),
		elapsedTime(0)
	{}

	float deltaTime;
	float elapsedTime;
};

}
