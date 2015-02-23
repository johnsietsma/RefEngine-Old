#include "TestBed.h"

#include <assert.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Gizmos.h"

static void errorCallback(int errorCode, const char* errorDesc)
{
	std::cerr << "GLFW Error(" << errorCode << "): " << errorDesc << std::endl;
}

void keyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, 1);
	}
}


TestBed::TestBed()
{
	// no-op
}

TestBed::~TestBed()
{
	Stop();
}

bool TestBed::Init()
{
	isValid = glfwInit() == GL_TRUE;
	if (!isValid) return false;

	pWindow = glfwCreateWindow(640, 480, "TestBed", nullptr, nullptr);
	isValid = pWindow != nullptr;

	if (!isValid) return false;

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(pWindow, keyCallback);

	glfwMakeContextCurrent(pWindow);
	glfwSwapInterval(1);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void TestBed::Stop()
{
	if (pWindow != nullptr) {
		glfwDestroyWindow(pWindow);
		pWindow = nullptr;
	}
	if (isValid) { glfwTerminate(); }

	isValid = false;
}

bool TestBed::Update() const
{
	if (glfwWindowShouldClose(pWindow)) return false;

	assert(pWindow != nullptr);

	int width, height;
	float ratio;

	glfwGetFramebufferSize(pWindow, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1, 1, 1, -1);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(-0.6f, -0.4f, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0.6f, -0.4f, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0.6f, 0);
	glEnd();

	glfwSwapBuffers(pWindow);
	glfwPollEvents();

	return true;
}
