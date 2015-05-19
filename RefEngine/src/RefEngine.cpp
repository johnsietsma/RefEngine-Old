#include "RefEngine.h"

#include "Camera.h"
#include "FBXFile.h"
#include "AssetManager.h"
#include "Color.h"
#include "Controller.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include <aie/Gizmos.h>
#include "gl_core_4_1.h"
#include "GLHelpers.h"
#include "Material.h"
#include "Mesh.h"
#include "pow2assert.h"
#include "Prims.h"
#include "SpinController.h"
#include "GameTime.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace reng;

static void errorCallback(int errorCode, const char* errorDesc)
{
	cerr << "GLFW Error(" << errorCode << "): " << errorDesc << endl;
}

void keyCallback(GLFWwindow* m_pWindow, int key, int /*scanCode*/, int action, int /*mods*/)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_pWindow, 1);
	}
}


RefEngine::RefEngine() :
	m_isValid(false),
	m_pAssetManager(new AssetManager()),
	m_pCamera(new Camera(glm::vec3(4, 3, 3), glm::vec3(0), 45, 16 / 9.f)),
	m_pTime(new GameTime())
{
}

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

std::shared_ptr<ComponentManager> RefEngine::GetComponentManager() const { return m_pEntityManager->GetComponentManager(); }

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
	Gizmos::create();


	// -----

	m_isValid = true;

	return true;
}

bool RefEngine::Update(float deltaTime)
{
	POW2_ASSERT(m_isValid);
	if (glfwWindowShouldClose(m_pWindow)) return false;

	m_pTime->deltaTime = deltaTime;
	m_pTime->elapsedTime += deltaTime;


	// TODO update components

	/*
	for (auto gameObject : m_gameObjects) {
		shared_ptr<Controller> pController = gameObject->GetController();
		if (pController != nullptr) {
			gameObject->GetController()->Update(deltaTime, gameObject);
		}
	}
	*/

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

	//m_pRenderer->Render(m_pCamera.get(), m_renderables);
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
