cd `dirname $0`
mkdir -p build/xcode
pushd build/xcode
cmake -DUSE_TESTS:BOOL=TRUE -DUSE_GLFW_WINDOW:BOOL=TRUE -G "Xcode" ../../
popd
