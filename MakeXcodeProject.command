cd `dirname $0`
mkdir build
pushd build
cmake -G "Xcode" ../
popd
