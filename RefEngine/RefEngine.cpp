#include "RefEngine.h"

#include "AssetManager.h"
#include "Camera.h"
#include "Color.h"

#include "component/RenderableComponent.h"
#include "component/LightComponent.h"

#include "debug/DebugGUI.h"

#include "entity/Entity.h"

#include "graphics/GLHelpers.h"
#include "graphics/OpenGLRenderer.h"

#include "utils/pow2assert.h"


#include <aie/Gizmos.h> // TODO: Remove
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace reng;


RefEngine::RefEngine() :
	m_pAssetManager(std::make_unique<AssetManager>()),
	m_pCamera(new Camera(glm::vec3(15, 18, -20), glm::vec3(0,5,0), 45, 16 / 9.f)),
    m_pComponentDatabase(std::make_unique<ComponentDatabase>()),
	m_pUpdateComponentProcessor(std::make_unique<ComponentProcessorManager>()),
    m_pRenderer(new OpenGLRenderer())
{
}

bool RefEngine::Init()
{
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED) return false;

    float clear = 192 / 255.f;
    glClearColor(clear, clear, clear, 1);
    glEnable(GL_DEPTH_TEST);
    
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

#ifdef _DEBUG
	GLHelpers::TurnOnDebugLogging();
#endif

    return true;
}

bool RefEngine::Update(double deltaTime)
{
	m_pUpdateComponentProcessor->Process( deltaTime, *m_pComponentDatabase.get() );
    return true;
}

void RefEngine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if( !m_pComponentDatabase->HasComponentContainer<RenderableComponent>() ) return;

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
}

Entity& RefEngine::EmplaceEntity(const char* pName)
{
    m_pEntities.emplace_back( std::make_unique<Entity>(pName, m_pComponentDatabase.get()) );
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
