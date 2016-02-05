#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace reng;

Camera::Camera(float fov, float aspectRatio, float nearClipDistance, float farClipDistance) :
	Camera( Transform(), fov, aspectRatio, nearClipDistance, farClipDistance )
{
}


Camera::Camera(const Transform& transform, float fov, float aspectRatio, float nearClipDistance, float farClipDistiance) :
	m_worldTransform( transform )
{
	SetProjection(fov, aspectRatio, nearClipDistance, farClipDistiance);
}

void Camera::SetProjection(float fov, float aspectRatio, float nearClipDistance, float farClipDistance)
{
	m_projection = glm::perspective(fov, aspectRatio, nearClipDistance, farClipDistance);
}

