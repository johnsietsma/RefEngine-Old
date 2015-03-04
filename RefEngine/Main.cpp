#include "TestBed.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

enum class Test { ONE, TWO };


int main(int argc, char** argv)
{
	std::cout << "Running TestBed: " << glfwGetVersionString() << std::endl;

	TestBed testBed;
    //std::string baseDir(argv[0]);
    std::string vertShader = "data/shaders/default.vert";
    std::string fragShader = "data/shaders/red.frag";
	if (!testBed.Init( "Dice", vertShader.c_str(), fragShader.c_str() ) ) {
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

	std::cout << "Finished running TestBed";
	return 0;
}

