#include "Processors.h"

#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "OpenGLRenderer.h"
#include "Transform.h"

#include <utility>

using namespace reng;

void RenderProcessor::DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager)
{
	auto transformContainer = componentManager.GetComponentContainer<Transform>();
	auto materialContainer = componentManager.GetComponentContainer<Material*>();
	auto meshContainer = componentManager.GetComponentContainer<Mesh*>();

	for ( auto entityId : entityIds )
	{
		Transform& transform = transformContainer->Get(entityId);
		Material* pMaterial = materialContainer->Get(entityId);
		Mesh* pMesh = meshContainer->Get(entityId);

		m_pRenderer->UseProgram( pMaterial->GetProgramId() );

		// TODO: Cache this
		pMaterial->UpdateUniforms(m_pCamera.get(), transform.GetMartix());

		m_pRenderer->Bind(*pMesh);
		m_pRenderer->Draw(*pMesh);
	}

	m_pRenderer->UnbindAll();
	m_pRenderer->UnuseProgram();
}
