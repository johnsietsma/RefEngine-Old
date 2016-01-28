#pragma once

#include <memory>
#include <vector>

#include "AssetManager.h"
#include "Camera.h"

#include "component/DebugComponent.h"
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
	ComponentDatabase* GetComponentDatabase() { return m_pComponentDatabase.get(); }

    template<typename T>
    void RegisterUpdateComponent()
    {
        // Add this component to be updated during the component processing stage.
		m_pUpdateComponentProcessor->RegisterComponentProcessor<T,double>( UpdateComponent::UpdateProcessor<T> );
    }

	template<typename T>
	void RegisterDebugComponent()
	{
		// Add this component to be updated during the component processing stage.
		m_pDebugComponentProcessor->RegisterComponentProcessor<T, double>(DebugComponent::DebugProcessor<T>);
	}

    template<typename T, typename TArg>
    void ProcessComponents(TArg arg, ComponentProcessorFunction<T,TArg> processorFunction)
    {
        if (!m_pComponentDatabase->HasComponentContainer<T>()) return;;
        auto& componentContainer = m_pComponentDatabase->GetComponentContainer<T>();
        processorFunction(arg, componentContainer);
    }

    Entity& EmplaceEntity( const char* pName );

private:

	void DrawWorldGrid() const;

	std::unique_ptr<AssetManager> m_pAssetManager;
	std::unique_ptr<Camera> m_pCamera;
    std::unique_ptr<ComponentDatabase> m_pComponentDatabase;
	std::unique_ptr<ComponentProcessorManager> m_pUpdateComponentProcessor;
	std::unique_ptr<ComponentProcessorManager> m_pDebugComponentProcessor;
    std::unique_ptr<OpenGLRenderer> m_pRenderer;
    std::vector<std::unique_ptr<Entity>> m_pEntities;

    DebugGUI m_debugGUI;
};

}
