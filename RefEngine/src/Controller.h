#pragma once

// fwd decls
class GameObject;

class Controller
{
public:
	virtual void Update(float deltaTime, GameObject* pGameObject) = 0;
};