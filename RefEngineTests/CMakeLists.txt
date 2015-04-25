cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RefEngineTests
    src/CachingFactoryTests.cpp
	src/ComponentContainerTests.cpp
	src/ComponentManagerTests.cpp
    src/EntityManagerTests.cpp
	src/IndexedContainerTests.cpp
	src/ProcessorTests.cpp
    src/VariadicHashTests.cpp
 )

IF(APPLE)
	# Fix for Macs looking for .dylib
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
ENDIF(APPLE)


target_link_libraries(RefEngineTests
    debug ${gtest_BINARY_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${gtest_BINARY_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
)
target_link_libraries(RefEngineTests
    debug ${gtest_BINARY_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${gtest_BINARY_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
)


target_link_libraries(RefEngineTests refeng)

add_test(
    NAME MethodBarDoesAbc
    COMMAND RefEngineTest)
