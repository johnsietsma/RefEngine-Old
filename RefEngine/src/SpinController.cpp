#include "SpinController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

using namespace reng;

/*
void SpinController::Update(float deltaTime, GameObject* pGameObject)
{
	glm::mat4 trans = pGameObject->GetTransform();
	trans = glm::rotate<float>(trans, 10 * deltaTime, glm::vec3(0,1.f,0));
	pGameObject->SetTransform(trans);
}
*/