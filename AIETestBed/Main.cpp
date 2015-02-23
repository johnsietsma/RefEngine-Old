#include <GLFW/glfw3.h>
#include <iostream>
#include <tchar.h>

#include "TestBed.h"

int _tmain(int argc, const char* argv[])
{
	std::cout << "Running TestBed: " << glfwGetVersionString() << std::endl;

	TestBed testBed;
	testBed.Init();
	while (testBed.Update()) {}
	testBed.Stop();

	std::cout << "Finished running TestBed";
	return 0;
}
