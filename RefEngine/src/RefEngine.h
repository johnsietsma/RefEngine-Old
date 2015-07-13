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
class RenderProcessor;
class OpenGLRenderer;
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

	GameTime* GetTime() const { return m_pTime.get(); }
	ComponentManager* GetComponentManager() const;
	EntityManager* GetEntityManager() const { return m_pEntityManager.get(); }

	void Run();
	bool Init();
	bool Update(double deltaTime);
	void Draw();

protected:
	virtual bool DoInit() = 0;
	virtual void DoUpdate(double deltaTime) = 0;

private:
	void DrawWorldGrid() const;

	bool m_isValid;
	GLFWwindow* m_pWindow;
	std::unique_ptr<AssetManager> m_pAssetManager;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<EntityManager> m_pEntityManager;
	std::shared_ptr<GameTime> m_pTime;
	std::shared_ptr<ProcessorManager> m_pProcessor;
	std::shared_ptr<OpenGLRenderer> m_pRenderer;

	std::shared_ptr<RenderProcessor> m_pRenderProcessor;
};

}
