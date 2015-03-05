#include "TestBed.h"

#include <aie/Gizmos.h>
#include <assert.h>
#include <FBXFile.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Buffer.h"
#include "Camera.h"
#include "Color.h"
#include "GameObject.h"
#include "GLHelpers.h"
#include "Material.h"
#include "Prims.h"
#include "Renderer.h"
#include "ShaderManager.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace std;



TestBed::TestBed() :
m_pRefEngine(new RefEngine())
{
}

bool TestBed::Init()
{

	/*if (!m_fbxFile.load(fbxFileName)) {
		std::cerr << "Couldn't load fbx file " << fbxFileName << std::endl;
		return false;
	}*/

	/*FBXMeshNode* meshNode = m_fbxFile.getMeshByName(meshName);
	if (meshNode == nullptr) {
		std::cerr << "Couldn't find mesh " << meshName << " in fbx file " << fbxFileName << std::endl;
		return false;
	}*/

	if (!m_pRefEngine->Init()) return false;
	return true;
}

bool TestBed::Update(double deltaTime)
{
	return m_pRefEngine->Update();
}

void TestBed::Draw() const
{
	m_pRefEngine->Draw();
}
