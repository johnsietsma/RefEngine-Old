#pragma once

#include <memory>
#include <vector>

#include "AssetManager.h"
#include "Camera.h"

#include "component/UpdateComponent.h"

#include "debug/DebugGUI.h"

#include "entity/ComponentDatabase.h"
#include "entity/ComponentProcessor.h"
#include "entity/Entity.h"

#include "graphics/OpenGLRenderer.h"

class FBXFile;

namespace reng {

class Entity;
class OpenGLRenderer;

class RefEngine
{
public:
	RefEngine();
	~RefEngine() = default;

    bool Init();
    bool Update(double deltaTime);
    void Draw();

    Camera* GetCamera() { return m_pCamera.get(); }
    AssetManager* GetAssetManager() { return m_pAssetManager.get(); }

    template<typename T>
    void RegisterUpdateComponent()
    {
        // Add this component to be updated during the component processing stage.
        m_pComponentProcessor->RegisterComponentProcessor<T>( UpdateComponent::UpdateProcessor<T> );
    }

    Entity& EmplaceEntity();

private:

	void DrawWorldGrid() const;

	std::unique_ptr<AssetManager> m_pAssetManager;
	std::unique_ptr<Camera> m_pCamera;
    std::unique_ptr<ComponentDatabase> m_pComponentDatabase;
    std::unique_ptr<ComponentProcessorManager> m_pComponentProcessor;
    std::unique_ptr<OpenGLRenderer> m_pRenderer;
    std::vector<std::unique_ptr<Entity>> m_pEntities;

    DebugGUI m_debugGUI;
};

}
