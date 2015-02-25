#include "Camera.h"

#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

Camera::Camera(const glm::vec3& eye, const glm::vec3& center, float fov, float aspectRatio)
{
	m_view = glm::lookAt(eye, center, vec3(0, 1, 0));
	m_projection = glm::perspective(fov, aspectRatio, 0.1f, 100.f);
}
