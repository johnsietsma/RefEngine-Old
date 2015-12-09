#pragma once

#include<memory>
#include <vector>

#include "Camera.h"

class FBXFile;
struct GLFWwindow;

namespace reng {

class AssetManager;
class IGameObject;
class OpenGLRenderer;

class RefEngine
{
public:
	RefEngine();
	~RefEngine();

    bool Init();
    void Run();

    void AddGameObject(IGameObject* pGameObject);
    
    template<class T,class ...TArgs>
    void EmplaceGameObject(TArgs... args) {
        m_gameObjects.emplace_back( std::make_unique<T>(args...) );
    }

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
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<OpenGLRenderer> m_pRenderer;
    std::vector<std::unique_ptr<IGameObject>> m_gameObjects;
};

}
