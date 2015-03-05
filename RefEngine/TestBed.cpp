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


static void errorCallback(int errorCode, const char* errorDesc)
{
	cerr << "GLFW Error(" << errorCode << "): " << errorDesc << endl;
}

void keyCallback(GLFWwindow* m_pWindow, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_pWindow, 1);
	}
}

TestBed::TestBed() :
	m_pCamera( new Camera(vec3(4, 3, 3), vec3(0), 45, 16/9.f) ),
	m_sphereTransform(mat4(1)),
	m_sphereRotationSpeed((glm::pi<float>()*2)/60),
	m_pRenderer(new Renderer())
{
	m_sphereTransform = glm::translate(m_sphereTransform, vec3(-20));
}

bool TestBed::Init( const char* meshName, const char* vertexShaderFileName, const char* fragmentShaderFileName )
{
	assert(meshName != nullptr);

	m_isValid = glfwInit() == GL_TRUE;
	if (!m_isValid) return false;
    
	// Required to get MacOS out of compatiblity mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_pWindow = glfwCreateWindow(640, 480, "TestBed", nullptr, nullptr);
	if (m_pWindow == nullptr) return false;

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(m_pWindow, keyCallback);

	glfwMakeContextCurrent(m_pWindow);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) return false;
    
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLHelpers::TurnOnDebugLogging();

	/*if (!m_fbxFile.load(fbxFileName)) {
		std::cerr << "Couldn't load fbx file " << fbxFileName << std::endl;
		return false;
	}*/

	/*FBXMeshNode* meshNode = m_fbxFile.getMeshByName(meshName);
	if (meshNode == nullptr) {
		std::cerr << "Couldn't find mesh " << meshName << " in fbx file " << fbxFileName << std::endl;
		return false;
	}*/

	auto programId = ShaderManager::MakeProgram(vertexShaderFileName, fragmentShaderFileName);
	if (programId == ProgramId_Invalid) return false;

	auto pBuffer = VertexBuffer::Create(Prims::TriangleSize, Prims::TriangleSize, Prims::Triangle);
	std::shared_ptr<Material> pMaterial( new Material(programId) );

	m_gameObjects.push_back(new GameObject(glm::vec3(0), pMaterial, pBuffer));
	m_gameObjects.push_back(new GameObject(glm::vec3(1,0,0), pMaterial, pBuffer));

	m_isModelLoaded = true;

	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	m_pRenderer->Init(width, height);
	Gizmos::create();

	m_isValid = true;

	return true;
}

void TestBed::Stop()
{
	if (!m_isValid) return;

	//m_pVertexArrayRenderer->Destroy();

	if (m_isModelLoaded) {
		m_fbxFile.unload();
	}

	if (m_pWindow != nullptr) {
		glfwDestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
	if (m_isValid) { glfwTerminate(); }

	Gizmos::destroy();

	m_isValid = false;
}

bool TestBed::Update(double deltaTime)
{
	if (glfwWindowShouldClose(m_pWindow)) return false;

	glfwPollEvents();

	return true;
}

void TestBed::Draw() const
{
	assert(m_pWindow != nullptr);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	DrawWorldGrid();

	m_pRenderer->Render(m_pCamera, m_gameObjects);
	Gizmos::draw(m_pCamera->GetProjectionView());

	glfwSwapBuffers(m_pWindow);
}

void TestBed::DrawWorldGrid() const
{
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? Color::White : Color::Black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? Color::White : Color::Black);
	}
}
