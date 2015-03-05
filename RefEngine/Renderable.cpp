#include "Renderable.h"

#include "Buffer.h"
#include "Material.h"
#include "pow2assert.h"

Renderable::Renderable(Material* pMaterial , Buffer* pBuffer) :
m_pMaterial(pMaterial),
m_pBuffer(pBuffer)
{
	POW2_ASSERT(pMaterial);
	POW2_ASSERT(pMaterial->GetProgramId() != ProgramId_Invalid);
	POW2_ASSERT(pBuffer);
}
