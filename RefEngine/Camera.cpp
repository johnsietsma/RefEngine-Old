#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetProjectionView() {
    return m_projection * m_view;
}


Camera::Camera(glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio)
{
	m_view = glm::lookAt(eye, center, glm::vec3(0, 1, 0));
	m_projection = glm::perspective(fov, aspectRatio, 0.1f, 100.f);
}
