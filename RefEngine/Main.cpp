#include "TestBed.h"

#include "RefEngine.h"

#ifdef _WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


int main(int argc, char** argv)
{
	char cCurrentPath[FILENAME_MAX];
	if (GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		printf("The current working directory is %s", cCurrentPath);
	}

	auto refEng = new RefEngine();
	if (!refEng->Init()) return 1;
	refEng->Run();

	return 0;
}

