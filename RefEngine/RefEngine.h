#pragma once

#include <memory>
#include <vector>

#define alignas(N) __declspec(align(N))

class Camera;
class Renderer;
class GameObject;
struct GLFWwindow;

class RefEngine
{
public:
	RefEngine();
	~RefEngine();

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
};

