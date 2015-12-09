#include "TestBed.h"
#include <iostream>

int main()
{
	TestBed testBed;
	if (!testBed.Init()) {
		return 1;
	}
	testBed.Run();

	return 0;
}

