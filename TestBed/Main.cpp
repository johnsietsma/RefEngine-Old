#include "TestBed.h"
#include <iostream>

int main()
{
	/*TestBed testBed;
	if (!testBed.Init()) {
		return 1;
	}
	testBed.Run();
    */

    struct Thing {
        //virtual void Foo() {}; // 4
        //int a;                 // 8
        //char b;                // 12
        //double c;              // 24
        char d;                // 32
    };

    std::cout << "sizeof: " << sizeof(Thing) << std::endl;

	return 0;
}

