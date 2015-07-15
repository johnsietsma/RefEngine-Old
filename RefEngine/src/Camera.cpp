#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace reng;

Camera::Camera(glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio) :
	m_worldTransform( glm::inverse(glm::lookAt(eye, center, glm::vec3(0, 1, 0))) )
{
	m_projection = glm::perspective(fov, aspectRatio, 0.1f, 100.f);
}

void Camera::LookAt(glm::vec3 lookAt, glm::vec3 worldUp)
{
	const glm::vec3& vLocation = m_worldTransform.GetPosition();
	m_worldTransform = glm::inverse(glm::lookAt(vLocation, lookAt, worldUp));
}
