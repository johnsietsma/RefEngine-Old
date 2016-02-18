mkdir build\VisualStudio2013
pushd build\VisualStudio2013

cmake -DUSE_TESTS:BOOL=TRUE -DUSE_GLFW_WINDOW:BOOL=TRUE -G "Visual Studio 12" ..\..\
popd
pause
