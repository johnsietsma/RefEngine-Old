#include "RefEngine.h"

#include "Camera.h"
#include "Renderer.h"

#include "FBXFile.h"


#include "pow2assert.h"
#include "Buffer.h"
#include "Color.h"
#include "Controller.h"
#include <aie/Gizmos.h>
#include "GameObject.h"
#include "gl_core_4_1.h"
#include "GLHelpers.h"
#include "Material.h"
#include "Renderable.h"
#include "Prims.h"
#include "ProgramManager.h"
#include "SpinController.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

static const VertexAttribute FBXVertexAttributes[9] = {
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, position), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, colour), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, normal), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, tangent), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, binormal), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, indices), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, weights), GL_FLOAT),
	VertexAttribute::Create<glm::vec2>(2, offsetof(FBXVertex, texCoord1), GL_FLOAT),
	VertexAttribute::Create<glm::vec2>(2, offsetof(FBXVertex, texCoord2), GL_FLOAT)
};


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


RefEngine::RefEngine() :
	m_isValid(false),
	m_pCamera(new Camera(glm::vec3(4, 3, 3), glm::vec3(0), 45, 16 / 9.f)),
	m_pRenderer(new Renderer()),
	m_pProgramManager(new ProgramManager())
{}

RefEngine::~RefEngine()
{
	if (m_pWindow != nullptr) {
		glfwDestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
	if (m_isValid) { glfwTerminate(); }

	Gizmos::destroy();

	m_isValid = false;
}

void RefEngine::Run()
{
	POW2_ASSERT_MSG(m_isValid, "Call Init() first and check return code.");

	double deltaTime = 0;
	double totalRunTime = glfwGetTime();
	bool isRunning = true;
	while (isRunning) {
		double currTime = glfwGetTime();
		deltaTime = currTime - totalRunTime;
		totalRunTime = currTime;
		isRunning = Update((float)deltaTime);
		Draw();
	}
}

bool RefEngine::Init()
{
	POW2_ASSERT(!m_isValid);
	std::cout << "Running TestBed: " << glfwGetVersionString() << std::endl;

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

	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	m_pRenderer->Init(width, height);
	Gizmos::create();

	//-----
	// TODO Move into external init section
	auto programId = m_pProgramManager->GetOrCreateProgram("data/shaders/default.vert", "data/shaders/red.frag");
	if (programId == ProgramId_Invalid) return false;

	Material* pMaterial = new Material(programId);

	// Put in a couple of tris
	auto pTriBuffer = VertexBuffer::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	Renderable* triRenderable = new Renderable(pMaterial, pTriBuffer);
	m_gameObjects.push_back(new GameObject(glm::vec3(-2, 0, 0), new SpinController(), triRenderable));
	m_gameObjects.push_back(new GameObject(glm::vec3(2, 0, 0), new SpinController(), triRenderable));

	// Add a cube
	auto pCubeBuffer = VertexBuffer::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);
	Renderable* cubeRenderable = new Renderable(pMaterial, pCubeBuffer);
	m_gameObjects.push_back(new GameObject(glm::vec3(0,0,-5), nullptr, cubeRenderable));

	// Add a fbx model
	m_fbx = new FBXFile();
	m_fbx->load("data/models/cube.fbx");

	for (uint i = 0; i < m_fbx->getMeshCount(); i++) {
		FBXMeshNode* pMesh = m_fbx->getMeshByIndex(i);
		if (pMesh->m_vertices.size() >  0) {
			uint numIndices = 0;
			uint* pIndices = nullptr;
			if (pMesh->m_indices.size() > 0) {
				numIndices = pMesh->m_indices.size();
				pIndices = &(pMesh->m_indices[0]);
			}


			auto pMeshBuffer = VertexBuffer::Create(
				pMesh->m_vertices.size(), &(pMesh->m_vertices[0]),
				numIndices, pIndices,
				sizeof(FBXVertexAttributes)/sizeof(VertexAttribute), FBXVertexAttributes
				);

			Renderable* fbxRenderable = new Renderable(pMaterial, pMeshBuffer);
			m_gameObjects.push_back(new GameObject(glm::vec3(0,0,3), nullptr, fbxRenderable));
		}
	}

	m_fbx->initialiseOpenGLTextures();

	// -----

	m_isValid = true;

	return true;
}

bool RefEngine::Update(float deltaTime)
{
	POW2_ASSERT(m_isValid);
	if (glfwWindowShouldClose(m_pWindow)) return false;

	for (auto gameObject : m_gameObjects) {
		shared_ptr<Controller> pController = gameObject->GetController();
		if (pController != nullptr) {
			gameObject->GetController()->Update(deltaTime, gameObject);
		}
	}

	glfwPollEvents();
	return true;
}

void RefEngine::Draw()
{
	POW2_ASSERT(m_pWindow != nullptr);
	POW2_ASSERT(m_isValid);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	DrawWorldGrid();

	m_pRenderer->Render(m_pCamera, m_gameObjects);
	Gizmos::draw(m_pCamera->GetProjectionView());

	glfwSwapBuffers(m_pWindow);
}


void RefEngine::DrawWorldGrid() const
{
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? Color::White : Color::Black);

		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? Color::White : Color::Black);
	}
}
