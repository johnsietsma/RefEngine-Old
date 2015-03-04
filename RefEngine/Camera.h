#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera( glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio );

	glm::mat4 GetProjectionView();

private:
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

