#pragma once

#include "utils/memaligned.h"

#include <glm/glm.hpp>

namespace reng {

class Camera
{
public:
	Camera( glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio );

	glm::mat4 GetProjectionView() const;

	void* operator new(size_t size){ return aligned_new(size, 16); }
	void operator delete(void* mem) { return aligned_delete(mem); }

private:
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

}