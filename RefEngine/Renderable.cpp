#include "Renderable.h"

#include "Buffer.h"
#include "Material.h"
#include "pow2assert.h"

Renderable::Renderable(std::shared_ptr<Material> pMaterial , std::shared_ptr<Buffer> pBuffer) :
m_pMaterial(pMaterial),
m_pBuffer(pBuffer)
{
	POW2_ASSERT(pMaterial.get());
	POW2_ASSERT(pMaterial->GetProgramId() != ProgramId_Invalid);
	POW2_ASSERT(pBuffer.get());
}
