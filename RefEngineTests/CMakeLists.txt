cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

enable_testing()
set(gtest_force_shared_crt ON)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RefEngineTests
    CachingFactoryTests.cpp
    VariadicHashTests.cpp
 )

IF(APPLE)
	# Fix for Macs looking for .dylib
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    SET(STD_C11 "-std=c++11 -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
ENDIF(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

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
