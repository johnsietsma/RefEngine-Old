#include "Processors.h"

#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "OpenGLRenderer.h"
#include "Transform.h"

using namespace reng;

void RenderProcessor(Camera* pCamera, OpenGLRenderer* pRenderer, ComponentIteratorPair<Mesh*> meshIters, ComponentIteratorPair<Material*> materialIters, ComponentIteratorPair<Transform> transformIters)
{
	ComponentIteratorPair<Mesh*>::iterator meshIt = meshIters.begin;
	ComponentIteratorPair<Material*>::iterator materialIt = materialIters.begin;
	ComponentIteratorPair<Transform>::iterator transformIt = transformIters.begin;

	while (meshIt != meshIters.end) {
		Material* pMaterial = materialIt.get();
		pRenderer->UseProgram( pMaterial->GetProgramId() );

		// TODO: Cache this
		pMaterial->UpdateUniforms(pCamera, transformIt->GetMartix());

		const Mesh *pMesh = meshIt.get();
		pRenderer->Bind(*pMesh);
		pRenderer->Draw(*pMesh);

		meshIt++; materialIt++; transformIt++;
	}

	pRenderer->UnbindAll();
	pRenderer->UnuseProgram();
}
