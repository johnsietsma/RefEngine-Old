#pragma once

#include "memaligned.h"

#include <glm/glm.hpp>
#include <memory>

class Controller;
class Renderable;

class GameObject
{
public:
	GameObject(const glm::vec3& position, Controller* pController, Renderable* pRenderable);

	const glm::mat4x4& GetTransform() const { return m_transform;  }
	void SetTransform(const glm::mat4& transform) { m_transform = transform;  }

	const std::shared_ptr<Controller> GetController() const { return m_pController; }
	const std::shared_ptr<Renderable> GetRenderable() const { return m_pRenderable; }

	void* operator new(size_t size){ return malloc_aligned(size, 16); }
	void operator delete(void* mem) { return free_aligned(mem); }
private:
	glm::mat4x4 m_transform;
	std::shared_ptr<Controller> m_pController;
	std::shared_ptr<Renderable> m_pRenderable;
};
