#include "Renderer.h"

#include "Buffer.h"
#include "Camera.h"
#include "GameObject.h"
#include "gl_core_4_1.h"
#include "Material.h"
#include "Renderable.h"

#include <iostream>

using namespace std;

void Renderer::Init(int width, int height)
{
	glViewport(0, 0, width, height);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

}

void Renderer::Render(std::shared_ptr<Camera> pCamera, std::shared_ptr<GameObject> pGameObject)
{
    auto pMaterial = pGameObject->GetMaterial();
	glm::mat4 MVP = pCamera->GetProjectionView() * pGameObject->GetTransform();

	GLuint programId = pMaterial->GetProgramId().Value();
	glUseProgram(programId);

	pGameObject->GetMaterial()->UpdateMVP(MVP);

	auto pBuffer = pGameObject->GetBuffer();
	//cout << "Rendering buffer: " << pBuffer->GetBufferId() << endl;

	pBuffer->Bind();
	pBuffer->Draw();

	glUseProgram(0);
}
