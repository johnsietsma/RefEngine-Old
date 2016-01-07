#include "RefEngine.h"

#include "AssetManager.h"
#include "Camera.h"
#include "Color.h"
#include "GameTime.h"

#include "component/RenderableComponent.h"
#include "component/LightComponent.h"

#include "debug/DebugGUI.h"

#include "entity/Entity.h"

#include "graphics/GLHelpers.h"
#include "graphics/OpenGLRenderer.h"

#include "utils/pow2assert.h"

#include <aie/Gizmos.h>
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
	m_pAssetManager(std::make_unique<AssetManager>()),
	m_pCamera(new Camera(glm::vec3(15, 18, -20), glm::vec3(0,5,0), 45, 16 / 9.f)),
    m_pComponentDatabase(std::make_unique<ComponentDatabase>()),
    m_pComponentProcessor(std::make_unique<ComponentProcessorManager>()),
    m_pRenderer(new OpenGLRenderer())
{
}

RefEngine::~RefEngine()
{
    if (m_isValid) Destroy();
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

	m_pWindow = glfwCreateWindow(1024, 780, "RefEng", nullptr, nullptr);
	if (m_pWindow == nullptr) return false;

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(m_pWindow, keyCallback);
	glfwMakeContextCurrent(m_pWindow);
	glfwSwapInterval(1);

	//int width, height;
	//glfwGetFramebufferSize(m_pWindow, &width, &height);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) return false;

	float clear = 192 / 255.f;
	glClearColor(clear, clear, clear, 1);

    glEnable(GL_DEPTH_TEST);
    
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

#ifndef NDEBUG
	GLHelpers::TurnOnDebugLogging();
#endif

	//Gizmos::create();

    m_debugGUI.Init(m_pWindow);

	m_isValid = true;

	return true;
}

void RefEngine::Destroy()
{
    POW2_ASSERT(m_isValid);

    if (m_pWindow != nullptr) {
        glfwDestroyWindow(m_pWindow);
        m_pWindow = nullptr;
    }
    if (m_isValid) { glfwTerminate(); }

    //Gizmos::destroy();

    m_isValid = false;
}

void RefEngine::Run()
{
    POW2_ASSERT_MSG(m_isValid, "Call Init() first and check return code.");

    double currentTime = glfwGetTime();
    double deltaTime = 1 / 60.f;
    double elapsedTime = 0;
    double accumulator = 0.0;
    bool isRunning = true;

    while (isRunning) {
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25) frameTime = 0.25;
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= deltaTime && isRunning) {
            isRunning = Update(deltaTime);
            elapsedTime += deltaTime;
            accumulator -= deltaTime;
        }
        Draw();
    }
}

bool RefEngine::Update(double deltaTime)
{
	POW2_ASSERT(m_isValid);
	if (glfwWindowShouldClose(m_pWindow)) return false;

	glfwPollEvents();

    m_pComponentProcessor->Process( deltaTime, *m_pComponentDatabase.get() );

	return true;
}

void RefEngine::Draw()
{
	POW2_ASSERT(m_pWindow != nullptr);
	POW2_ASSERT(m_isValid);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Gizmos::addTransform(glm::mat4(1));
	//DrawWorldGrid();

	Gizmos::draw(m_pCamera->GetProjectionViewMatrix());

    glm::vec3 lightDirection;
    glm::vec3 lightColor;

    if (m_pComponentDatabase->HasComponentContainer<LightComponent>()) {
        auto& lightContainer = m_pComponentDatabase->GetComponentContainer<LightComponent>();
        for (auto& light : lightContainer)
        {
            lightDirection = light.GetDirection();
            lightColor = light.GetColor();
            break; // Just one light for now;
        }
    }

    auto& renderablesContainer = m_pComponentDatabase->GetComponentContainer<RenderableComponent>();

    // Update lighting values
    // TODO: Update light directions
    // TODO: Check to see if cam has moved before updating values.
    // TODO: Collate lit materials.
    glm::vec3 camPos = GetCamera()->GetTransform().GetPosition();
    for (auto renderable : renderablesContainer) {
        Material* pMaterial = renderable.GetMaterial();
        if (pMaterial->IsLit()) {
            pMaterial->SetCameraPosition(camPos);
            pMaterial->SetLightDirection(lightDirection);
            pMaterial->SetLightColor(lightColor);
        }
    }

    // Render everything
    for (const auto& renderable : renderablesContainer) {
        renderable.Draw(m_pRenderer.get(), m_pCamera.get());
    }

    m_debugGUI.Draw();

	glfwSwapBuffers(m_pWindow);
}

Entity& RefEngine::EmplaceEntity()
{
    m_pEntities.emplace_back( std::make_unique<Entity>(m_pComponentDatabase.get()) );
    return *m_pEntities.back().get();
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
