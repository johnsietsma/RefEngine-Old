#include "RenderableGameObject.h"

#include "Camera.h"
#include "graphics\OpenGLRenderer.h"
#include "graphics\Material.h"

using namespace reng;

void RenderableGameObject::Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const
{
    pRenderer->UseProgram(m_pMaterial->GetProgramId());

    // TODO: Cache this
    m_pMaterial->UpdateUniforms(pCamera->GetProjectionViewMatrix(), m_transform.GetMartix());

    pRenderer->Bind(*m_pMesh);
    pRenderer->Draw(*m_pMesh);

    pRenderer->Unbind();
    pRenderer->UnuseProgram();
}

