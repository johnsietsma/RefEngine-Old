#pragma once

#include <FBXFile.h>
#include <glm/fwd.hpp>

#include "Camera.h"
#include "gl_core_4_4.h"

// fwd decls
struct GLFWwindow;

class TestBed
{
public:
	TestBed();
	~TestBed();

	bool Init(const char* fbxFileName, const char* meshName, const char* vertexShaderFileName, const char* fragmentShaderFileName);
	bool Update(double deltaTime);
	void Draw() const;
	void Stop();

private:
	void InitVertexBuffer();
	bool InitShaders( const char* vertexShaderFileName, const char* fragmentShaderFileName );

	void DrawWorldGrid() const;
	void DrawSolarSystem() const;
	void DrawFBXFile() const;
	void UpdateSolarSystem(double deltaTime);

	bool m_isValid;
	GLFWwindow* m_pWindow;
	Camera m_camera;

	glm::mat4 m_sphereTransform;
	float m_sphereRotationSpeed;
	FBXFile m_fbxFile;
	bool m_isModelLoaded;

	GLuint m_vertexArrayId;
	GLuint m_vertexBufferId;
	GLuint m_programId;
};

