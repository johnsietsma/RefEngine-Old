#include "GameObject.h"

#include "OpenGLTypes.h"
#include "Material.h"
#include "pow2assert.h"


GameObject::GameObject(const glm::vec3& position, std::shared_ptr<Material> pMaterial, std::shared_ptr<Buffer> buffer)
: m_pMaterial(pMaterial)
, m_pBuffer(buffer)
{
	glm::vec4 pos = glm::vec4(position, 1);
	glm::mat4 trans = glm::mat4(1.0f);
	trans[3] = pos;
	m_transform = trans;
	POW2_ASSERT(pMaterial.get());
	POW2_ASSERT(pMaterial->GetProgramId()!=ProgramId_Invalid);
	POW2_ASSERT(buffer.get());
}
