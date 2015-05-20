#include "Processors.h"

#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "OpenGLRenderer.h"
#include "Transform.h"

using namespace reng;

void RenderProcessor::Process(std::tuple<ComponentIteratorPair<Mesh*>, ComponentIteratorPair<Material*>, ComponentIteratorPair<Transform>> iterators)
{
	Process(std::get<0>(iterators), std::get<1>(iterators), std::get<2>(iterators));
}


void RenderProcessor::Process(ComponentIteratorPair<Mesh*> meshIters, ComponentIteratorPair<Material*> materialIters, ComponentIteratorPair<Transform> transformIters)
{
	ComponentIteratorPair<Mesh*>::iterator meshIt = meshIters.begin();
	ComponentIteratorPair<Material*>::iterator materialIt = materialIters.begin();
	ComponentIteratorPair<Transform>::iterator transformIt = transformIters.begin();

	while (meshIt != meshIters.end()) {
		Material* pMaterial = materialIt.get();
		m_pRenderer->UseProgram( pMaterial->GetProgramId() );

		// TODO: Cache this
		pMaterial->UpdateUniforms(m_pCamera.get(), transformIt->GetMartix());

		const Mesh *pMesh = meshIt.get();
		m_pRenderer->Bind(*pMesh);
		m_pRenderer->Draw(*pMesh);

		meshIt++; materialIt++; transformIt++;
	}

	m_pRenderer->UnbindAll();
	m_pRenderer->UnuseProgram();
}
