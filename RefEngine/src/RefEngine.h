#pragma once

#include <vector>

class Camera;
class FBXFile;
class GameObject;
struct GLFWwindow;
class Renderer;

namespace reng {

class AssetContainer;

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

	void Run();
	bool Init();
	bool Update(float deltaTime);
	void Draw();
private:
	void DrawWorldGrid() const;

	bool m_isValid;
	GLFWwindow* m_pWindow;
	Camera* m_pCamera;
	Renderer* m_pRenderer;
	AssetContainer* m_pAssetContainer;
	std::vector<GameObject*> m_gameObjects;
	FBXFile* m_fbx;
};

}
