#pragma once

#include <memory>
#include <vector>

class Camera;
class FBXFile;
class Renderer;
class GameObject;
struct GLFWwindow;

class RefEngine
{
public:
	RefEngine();
	~RefEngine();

	RefEngine( const RefEngine& ) = delete;

	void Run();
	bool Init();
	bool Update(float deltaTime);
	void Draw();
private:
	void DrawWorldGrid() const;

	bool m_isValid;
	GLFWwindow* m_pWindow;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Renderer> m_pRenderer;
	std::vector<GameObject*> m_gameObjects;

	FBXFile* m_fbx;
};

