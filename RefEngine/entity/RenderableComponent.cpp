#include "RenderableComponent.h"

#include "Entity.h"

#include "Camera.h"
#include "Transform.h"

#include "graphics/OpenGLRenderer.h"
#include "graphics/Material.h"

using namespace reng;

void RenderableComponent::Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const
{
    pRenderer->UseProgram(m_pMaterial->GetProgramId());

    auto& transform = m_transformComponentHandle.GetComponent().GetTransform();

    // TODO: Cache this
    m_pMaterial->UpdateUniforms(pCamera->GetProjectionViewMatrix(), transform.GetMartix());
    m_pMaterial->BindTexture();

    pRenderer->Bind(*m_pMesh);
    pRenderer->Draw(*m_pMesh);

    pRenderer->Unbind();
    pRenderer->UnuseProgram();
}

