#pragma once

#include "memaligned.h"

#include <glm/glm.hpp>

class Camera
{
public:
	Camera( glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio );

	glm::mat4 GetProjectionView() const;

	void* operator new(size_t size){ return malloc_aligned(size, 16); }
	void operator delete(void* mem) { return free_aligned(mem); }
    
private:
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

