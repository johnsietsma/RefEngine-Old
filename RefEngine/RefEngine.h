#pragma once

#include <memory>
#include <vector>

#include "Camera.h"

#include "component/UpdateComponent.h"

#include "entity/ComponentDatabase.h"
#include "entity/ComponentProcessor.h"

class FBXFile;
struct GLFWwindow;

namespace reng {

class AssetManager;
class Entity;
class OpenGLRenderer;

class RefEngine
{
public:
	RefEngine();
	~RefEngine();

    bool Init();
    void Run();

    GLFWwindow* GetWindow() { return m_pWindow; }
    Camera* GetCamera() { return m_pCamera.get(); }

    template<typename T>
    void RegisterUpdateComponent()
    {
        // Add this component to be updated during the component processing stage.
        m_pComponentProcessor->RegisterComponentProcessor<T>( UpdateComponent::UpdateProcessor<T> );
    }

    Entity& EmplaceEntity();

private:

    bool Update(double deltaTime);
    void Draw();
	void DrawWorldGrid() const;
    void Destroy();

	bool m_isValid;

	GLFWwindow* m_pWindow;
	std::unique_ptr<AssetManager> m_pAssetManager;
	std::unique_ptr<Camera> m_pCamera;
    std::unique_ptr<ComponentDatabase> m_pComponentDatabase;
    std::unique_ptr<ComponentProcessorManager> m_pComponentProcessor;
    std::unique_ptr<OpenGLRenderer> m_pRenderer;
    std::vector<std::unique_ptr<Entity>> m_pEntities;
};

}
