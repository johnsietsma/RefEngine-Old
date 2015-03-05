#pragma once

#include "Controller.h"

class SpinController : public Controller
{
public:
	void Update(float deltaTime, GameObject* pGameObject);
};