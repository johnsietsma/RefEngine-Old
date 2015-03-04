#include "TestBed.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <tchar.h>

enum class Test { ONE, TWO };


int _tmain(int argc, const char* argv[])
{
	std::cout << "Running TestBed: " << glfwGetVersionString() << std::endl;

	TestBed testBed;
	if (!testBed.Init( "data/dice/dice12.fbx", "Dice", "data/shaders/default.vert", "data/shaders/red.frag" )) { 
		std::cout << "Init failed" << std::endl;
		return 1; 
	}

	double deltaTime = 0;
	double totalRunTime = glfwGetTime();
	bool isRunning = true;
	while (isRunning) {
		double currTime = glfwGetTime();
		deltaTime = currTime - totalRunTime;
		totalRunTime = currTime;
		isRunning = testBed.Update(deltaTime);
		testBed.Draw();
	}
	testBed.Stop();

	Test t = Test::ONE;

	std::cout << "Finished running TestBed";
	return 0;
}

