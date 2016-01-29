#include "RenderableComponent.h"

#include "entity/Entity.h"

#include "Camera.h"
#include "Transform.h"

#include "component/TransformComponent.h"

#include "graphics/OpenGLRenderer.h"
#include "graphics/Material.h"

using namespace reng;

void RenderableComponent::Draw(OpenGLRenderer* pRenderer, Camera* pCamera, ComponentContainer<TransformComponent>& transformContainer) const
{
    pRenderer->UseProgram(m_pMaterial->GetProgramId());

	auto& transform = transformContainer.GetComponent(m_transformComponentHandle.id).GetTransform();

    // TODO: Cache this
    m_pMaterial->UpdateUniforms(pCamera->GetProjectionViewMatrix(), transform.GetMartix());
    m_pMaterial->BindTexture();

    pRenderer->Bind(*m_pMesh);
    pRenderer->Draw(*m_pMesh);

    pRenderer->Unbind();
    pRenderer->UnuseProgram();
}

