#include "Renderable.h"

#include "Mesh.h"
#include "Material.h"
#include "pow2assert.h"
#include "Transform.h"

using namespace reng;

Renderable::Renderable(Material* pMaterial , Mesh* pMesh, Transform* pTransform) :
m_pMaterial(pMaterial),
m_pMesh(pMesh),
m_pTransform(pTransform)
{
	POW2_ASSERT(pMaterial && pMaterial->GetProgramId() != ProgramId_Invalid);
	POW2_ASSERT(pMesh);
}
