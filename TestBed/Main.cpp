#include "TestBed.h"

#include "types.h"
#include <vector>

#include <OpenGLTypes.h>

#ifdef _WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


int main()
{
	TestBed testBed;
	if (!testBed.Init()) {
		return 1;
	}
	testBed.Run();

	return 0;
}

