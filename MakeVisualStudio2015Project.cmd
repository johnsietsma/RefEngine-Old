mkdir build\VisualStudio2015
pushd build\VisualStudio2015

cmake -DUSE_TESTS:BOOL=TRUE -DUSE_GLFW_WINDOW:BOOL=TRUE -G "Visual Studio 14" ..\..\
popd
pause
