#include "RefEngine.h"

#include "pow2assert.h"
#include "Buffer.h"
#include "Camera.h"
#include "Color.h"
#include "Controller.h"
#include <aie/Gizmos.h>
#include "GameObject.h"
#include "gl_core_4_1.h"
#include "GLHelpers.h"
#include "Material.h"
#include "Renderer.h"
#include "Renderable.h"
#include "Prims.h"
#include "ShaderManager.h"
#include "SpinController.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace glm;
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


RefEngine::RefEngine() :
	m_isValid(false),
	m_pCamera(new Camera(vec3(4, 3, 3), vec3(0), 45, 16 / 9.f)),
	m_pRenderer(new Renderer())
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
	auto programId = ShaderManager::MakeProgram("data/shaders/default.vert", "data/shaders/red.frag");
	if (programId == ProgramId_Invalid) return false;

	auto pBuffer = VertexBuffer::Create(Prims::TriangleSize, Prims::TriangleSize, Prims::Triangle);
	std::shared_ptr<Material> pMaterial(new Material(programId));
	shared_ptr<Renderable> triRenderable(new Renderable(pMaterial, pBuffer));

	m_gameObjects.push_back(new GameObject(glm::vec3(0), shared_ptr<Controller>(new SpinController()), triRenderable));
	m_gameObjects.push_back(new GameObject(glm::vec3(1,0,0), nullptr, triRenderable));
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

	m_pRenderer->Render(m_pCamera.get(), m_gameObjects);
	Gizmos::draw(m_pCamera->GetProjectionView());

	glfwSwapBuffers(m_pWindow);
}


void RefEngine::DrawWorldGrid() const
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
