#include "Renderer.h"

#include "Camera.h"
#include "GameObject.h"
#include "gl_core_4_4.h"
#include "Material.h"
#include "OpenGLOperators.h"
#include "Renderable.h"

Renderer::Renderer()
: m_openGLOperators(new OpenGLOperators())
{}

void Renderer::Init(int width, int height)
{
	glViewport(0, 0, width, height);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

}

void Renderer::Render(std::shared_ptr<Camera> pCamera, std::shared_ptr<GameObject> pGameObject)
{
	glm::mat4 MVP = pCamera->GetProjectionView() * pGameObject->GetTransform();
	glUseProgram(pGameObject->GetMaterial()->GetProgramId().Value());

	pGameObject->GetMaterial()->UpdateMVP(MVP);

	auto pBuffer = pGameObject->GetBuffer();
	GLenum bufferType = pBuffer->GetBufferType();
	GLuint bufferId = pBuffer->GetBufferId().Value();


	m_openGLOperators->BindBuffer(pBuffer);
	glBindBuffer(bufferType, bufferId );
	
}
