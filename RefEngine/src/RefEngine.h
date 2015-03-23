#pragma once

#include<memory>
#include <vector>

class FBXFile;
struct GLFWwindow;

namespace reng {

class AssetManager;
class Camera;
class ComponentManager;
struct EntityId;
class GameObject;
class Renderable;
class Renderer;
class GameTime;
class Transform;

class RefEngine
{
public:
	RefEngine();
	~RefEngine();

	// Disallow copying and moving
	RefEngine( const RefEngine& ) = delete;
	RefEngine( RefEngine&& ) = delete;
	RefEngine& operator=( const RefEngine& ) = delete;
	RefEngine& operator=( RefEngine&& ) = delete;

	GameTime* GetTime() const { return m_pTime.get(); }
	ComponentManager* GetComponentManager() const { return m_pComponentManager.get(); }

	void Run();
	bool Init();
	bool Update(float deltaTime);
	void Draw();
private:
	void DrawWorldGrid() const;

	bool m_isValid;
	GLFWwindow* m_pWindow;
	std::shared_ptr<AssetManager> m_pAssetManager;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<ComponentManager> m_pComponentManager;
	std::shared_ptr<GameTime> m_pTime;
	std::shared_ptr<Renderer> m_pRenderer;
	std::vector<Transform> m_transforms;
	std::vector<Renderable> m_renderables;
};

}
