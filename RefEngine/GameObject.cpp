#include "GameObject.h"

#include "OpenGLTypes.h"
#include "Material.h"
#include "pow2assert.h"


GameObject::GameObject(const glm::mat4x4& transform, std::shared_ptr<Material> pMaterial, std::shared_ptr<Buffer> buffer)
: m_transform(transform)
, m_pMaterial(pMaterial)
, m_pBuffer(buffer)
{
	POW2_ASSERT(pMaterial.get());
	POW2_ASSERT(pMaterial->GetProgramId()!=ProgramId_Invalid);
	POW2_ASSERT(buffer.get());
}
