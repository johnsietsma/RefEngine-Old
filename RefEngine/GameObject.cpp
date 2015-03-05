#include "GameObject.h"

#include "OpenGLTypes.h"
#include "Material.h"
#include "Renderable.h"
#include "pow2assert.h"


GameObject::GameObject(const glm::vec3& position, Controller* pController, Renderable* pRenderable) :
m_pController(pController),
m_pRenderable(pRenderable)
{
	glm::vec4 pos = glm::vec4(position, 1);
	glm::mat4 trans = glm::mat4(1.0f);
	trans[3] = pos;
	m_transform = trans;
}
