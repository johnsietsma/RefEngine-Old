#include "TestBed.h"

#include <aie/Gizmos.h>
#include <assert.h>
#include <FBXFile.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

#include "Camera.h"
#include "Color.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace std;



static void errorCallback(int errorCode, const char* errorDesc)
{
	std::cerr << "GLFW Error(" << errorCode << "): " << errorDesc << std::endl;
}

void keyCallback(GLFWwindow* m_pWindow, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_pWindow, 1);
	}
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
	// TODO
}

string readFile(const char* fileName)
{
	ifstream ifs(fileName, ios::in | ios::binary | ios::ate);
	if (!ifs.is_open()) return "";

	ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	vector<char> bytes(fileSize);
	ifs.read(&bytes[0], fileSize);

	return string(&bytes[0], fileSize);
}

bool checkCompileStatus( GLuint shaderId )
{
	GLint result = GL_FALSE;
	int logLength;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetShaderInfoLog(shaderId, logLength, NULL, logBuffer);
		cout << "Compile Error: " << logBuffer << endl;
		delete logBuffer;
		return false;
	}
	return true;
}

bool checkLinkStatus(GLuint programId)
{
	GLint result = GL_FALSE;
	int logLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetProgramInfoLog(programId, logLength, NULL, logBuffer);
		cout << "Link Error: " << logBuffer << endl;
		delete logBuffer;
		return false;
	}
	return true;
}

GLuint LoadShader(const char* shaderFileName, GLenum shaderType )
{
	GLuint shaderId = glCreateShader(shaderType);
	string shaderSource = readFile(shaderFileName);
	if (shaderSource.length()==0) {
		cerr << "Can't load ";
		switch (shaderType) {
		case GL_VERTEX_SHADER: cerr << "vertex"; break;
		case GL_FRAGMENT_SHADER: cerr << "fragment"; break;
		default: cerr << shaderType; break;
		}
		cerr << " shader : " << shaderFileName << endl;
		return -1;
	}

	const char* shaderSourceBuffer = shaderSource.c_str();
	glShaderSource(shaderId, 1, &shaderSourceBuffer, NULL);
	glCompileShader(shaderId);

	if (!checkCompileStatus(shaderId) ) {
		return -1;
	}

	return shaderId;

}



TestBed::TestBed() : 
	m_camera(vec3(10, 10, 10), vec3(0), 50, 16/9.f),
	m_sphereTransform(mat4(1)),
	m_sphereRotationSpeed((glm::pi<float>()*2)/60)
{
	m_sphereTransform = glm::translate(m_sphereTransform, vec3(-20));
}

TestBed::~TestBed()
{
	Stop();
}

bool TestBed::Init( const char* fbxFileName, const char* meshName, const char* vertexShaderFileName, const char* fragmentShaderFileName )
{
	assert(fbxFileName != nullptr);
	assert(meshName != nullptr);

	m_isValid = glfwInit() == GL_TRUE;
	if (!m_isValid) return false;

	m_pWindow = glfwCreateWindow(640, 480, "TestBed", nullptr, nullptr);
	if (m_pWindow == nullptr) return false;

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(m_pWindow, keyCallback);

	//TODO
	//glDebugMessageCallback(&glDebugCallback);

	glfwMakeContextCurrent(m_pWindow);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) return false;
	
	if (!m_fbxFile.load(fbxFileName)) {
		std::cerr << "Couldn't load fbx file " << fbxFileName << std::endl;
		return false;
	}

	FBXMeshNode* meshNode = m_fbxFile.getMeshByName(meshName);
	if (meshNode == nullptr) {
		std::cerr << "Couldn't find mesh " << meshName << " in fbx file " << fbxFileName << std::endl;
		return false;
	}

	InitVertexBuffer();

	if (!InitShaders(vertexShaderFileName, fragmentShaderFileName)) { return false; }

	m_isModelLoaded = true;
	

	glfwSwapInterval(1);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	glViewport(0, 0, width, height);

	Gizmos::create();

	m_isValid = true;

	return true;
}

void TestBed::InitVertexBuffer()
{
	const float vertexBufferData[] = {
		-1.f, -1.f, 0.f, 
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f
	};

	//glGenVertexArrays(1, &m_vertexArrayID);
	//glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool TestBed::InitShaders( const char* vertexShaderFileName, const char* fragmentShaderFileName )
{
	GLuint vertexShaderId = LoadShader(vertexShaderFileName, GL_VERTEX_SHADER);
	GLuint fragmentShaderId = LoadShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);

	if (vertexShaderId == (GLuint)-1 || fragmentShaderId == (GLuint)-1) { return false; }

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	if (!checkLinkStatus(programId)) {
		return false;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	m_programId = programId;

	return true;
}

void TestBed::Stop()
{
	if (m_isModelLoaded) {
		m_fbxFile.unload();
	}

	if (m_pWindow != nullptr) {
		glfwDestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
	if (m_isValid) { glfwTerminate(); }

	Gizmos::destroy();

	//TODO Clean up vertex buffer and shaders

	m_isValid = false;
}

bool TestBed::Update(double deltaTime)
{
	if (glfwWindowShouldClose(m_pWindow)) return false;

	UpdateSolarSystem(deltaTime);
	glfwPollEvents();

	return true;
}

void TestBed::Draw() const
{
	assert(m_pWindow != nullptr);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_programId);

	//Gizmos::clear();
	//Gizmos::addTransform(glm::mat4(1));

	//DrawWorldGrid();
	//DrawSolarSystem();
	DrawFBXFile();

	//Gizmos::draw(m_camera.GetProjectionView());

	glfwSwapBuffers(m_pWindow);
}

void TestBed::UpdateSolarSystem(double deltaTime)
{
	const vec3 up = vec3(0, 1, 0);
	mat4 rot = glm::rotate(m_sphereRotationSpeed*(float)deltaTime, up);
	m_sphereTransform *= rot;
}


void TestBed::DrawWorldGrid() const
{
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? Color::White : Color::Black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? Color::White : Color::Black);
	}
}

void TestBed::DrawSolarSystem() const
{
	Gizmos::addSphere(vec3(-5), 2, 15, 15, Color::Red, &m_sphereTransform);
}

void TestBed::DrawFBXFile() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}