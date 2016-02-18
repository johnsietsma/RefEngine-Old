# AIETestBed
My playground for trying out graphics and engine techniques. Definitely not best practices!

# Dependencies
You must install the FBX SDK. If you install to a non-default location please update the path in RefEngine/RefEngine/CMakeLists.txt

#Building
Pre-built projects for various build environments are provided in the "build" directory.

## From CMake
If your IDE isn't in the build directory or you'd like to build using CMak there are shell scripts and batch files to easily create projects for various development environments.

#Testing
RefEngine uses [GoogleTest](https://code.google.com/p/googletest/).
To make tests easy to run in VisualStudio you can use [GoogleTest Runner](https://visualstudiogallery.msdn.microsoft.com/9dd47c21-97a6-4369-b326-c562678066f0)
