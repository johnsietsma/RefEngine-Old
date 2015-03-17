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

void Renderer::Render(Camera* pCamera, vector<GameObject*> gameObjects)
{
	for (const GameObject* pGameObject : gameObjects) {
		auto pRenderable = pGameObject->GetRenderable();
		auto pMaterial = pRenderable->GetMaterial();

		GLuint programId = pMaterial->GetProgramId().Value();
		glUseProgram(programId);

		pMaterial->UpdateUniforms(pCamera, pGameObject);

		auto pBuffer = pRenderable->GetBuffer();

		pBuffer->Bind();
		pBuffer->Draw();
		pBuffer->Unbind();

		glUseProgram(0);
	}
}
