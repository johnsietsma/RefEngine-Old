#pragma once

#include<memory>
#include <vector>

class FBXFile;
struct GLFWwindow;

namespace reng {

class AssetManager;
class Camera;
class ComponentManager;
class EntityManager;
class GameTime;
class ProcessorManager;

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

	std::shared_ptr<GameTime> GetTime() const { return m_pTime; }
	std::shared_ptr<ComponentManager> GetComponentManager() const;
	std::shared_ptr<EntityManager> GetEntityManager() const { return m_pEntityManager; }

	void Run();
	bool Init();
	bool Update(float deltaTime);
	void Draw();
private:
	void DrawWorldGrid() const;

	bool m_isValid;
	GLFWwindow* m_pWindow;
	std::unique_ptr<AssetManager> m_pAssetManager;
	std::unique_ptr<Camera> m_pCamera;
	std::shared_ptr<EntityManager> m_pEntityManager;
	std::shared_ptr<GameTime> m_pTime;
	std::shared_ptr<ProcessorManager> m_pProcessor;
};

}
