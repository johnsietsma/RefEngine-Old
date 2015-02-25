#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera( const glm::vec3& eye, const glm::vec3& center, float fov, float aspectRatio );

	inline glm::mat4 GetProjectionView() const;

private:
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

inline glm::mat4 Camera::GetProjectionView() const {
	return m_projection * m_view;
}