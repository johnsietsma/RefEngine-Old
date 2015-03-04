#pragma once

#include <FBXFile.h>
#include <glm/fwd.hpp>
#include <memory>

#include "Camera.h"
#include "OpenGLTypes.h"

// fwd decls
struct GLFWwindow;
class Renderer;

class GameObject;

class TestBed
{
public:
	TestBed();

	bool Init(const char* meshName, const char* vertexShaderFileName, const char* fragmentShaderFileName);
	bool Update(double deltaTime);
	void Draw() const;
	void Stop();

private:
	void DrawWorldGrid() const;
	void DrawSolarSystem() const;
	void UpdateSolarSystem(double deltaTime);

	bool m_isValid;
	GLFWwindow* m_pWindow;
	std::shared_ptr<Camera> m_pCamera;

	glm::mat4 m_sphereTransform;
	float m_sphereRotationSpeed;
	FBXFile m_fbxFile;
	bool m_isModelLoaded;
	std::shared_ptr<Renderer> m_pRenderer;
	std::shared_ptr<GameObject> m_pSimpleTriVBO;
};

