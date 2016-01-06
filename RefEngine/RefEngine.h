#pragma once

#include <memory>
#include <vector>

#include "Camera.h"

#include "entity/ComponentDatabase.h"
#include "entity/ComponentProcessor.h"
#include "entity/UpdateComponent.h"

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

    template<typename T>
    void RegisterUpdateComponent()
    {
        m_pComponentProcessor->RegisterUpdateProcessor<T>( UpdateComponent::UpdateProcessor<T> );
    }

    Entity& EmplaceEntity();


protected:
	GLFWwindow* GetWindow() { return m_pWindow;  }
	Camera* GetCamera() { return m_pCamera.get(); }

	virtual bool DoInit() = 0;
	virtual void DoUpdate(double deltaTime) = 0;
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
