#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace reng;

Camera::Camera(float fov, float aspectRatio, float nearClipDistance, float farClipDistance) :
	Camera( glm::vec3(0,2,2), glm::vec3(0,0,0), fov, aspectRatio, nearClipDistance, farClipDistance ) // Point down z-axis by default
{
}


Camera::Camera(glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio, float nearClipDistance, float farClipDistiance) :
	m_worldTransform( eye, center )
{
	SetProjection(fov, aspectRatio, nearClipDistance, farClipDistiance);
}

void Camera::SetProjection(float fov, float aspectRatio, float nearClipDistance, float farClipDistance)
{
	m_projection = glm::perspective(fov, aspectRatio, nearClipDistance, farClipDistance);
}


void Camera::LookAt(glm::vec3 lookAt, glm::vec3 worldUp)
{
	const glm::vec3& vLocation = m_worldTransform.GetPosition();
	m_worldTransform = glm::inverse(glm::lookAt(vLocation, lookAt, worldUp));
}
