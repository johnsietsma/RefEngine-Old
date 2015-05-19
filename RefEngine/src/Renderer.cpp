#include "Renderer.h"

#include "Camera.h"
#include "gl_core_4_1.h"
#include "Material.h"

#include "OpenGLRenderer.h"

#include <iostream>

using namespace std;
using namespace reng;

/*
Renderer::Renderer() :
m_pRendererImpl(new OpenGLRenderer())
{}
*/

/*
void Renderer::Init(int width, int height)
{
	glViewport(0, 0, width, height);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

}
*/

/*
void Renderer::Render(const Camera* pCamera, const vector<Renderable>& renderables) const
{
	for (const Renderable& renderable : renderables) {
		auto pMaterial = renderable.GetMaterial();

		m_pRendererImpl->UseProgram(pMaterial->GetProgramId());
		pMaterial->UpdateUniforms(pCamera, renderable.GetTransform());
		auto pMesh = renderable.GetMesh();
		m_pRendererImpl->Bind(*pMesh);
		m_pRendererImpl->Draw(*pMesh);
	}

	m_pRendererImpl->UnbindAll();
	m_pRendererImpl->UnuseProgram();

}

*/