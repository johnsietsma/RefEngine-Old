#pragma once

#include "Controller.h"

namespace reng {

class SpinController : public Controller
{
public:
	void Update(float deltaTime, GameObject* pGameObject);
};

}