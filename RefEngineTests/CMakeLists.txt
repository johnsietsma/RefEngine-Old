cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RefEngineTests
    src/Tests.cpp
    src/ContainerTests.cpp
    src/VariadicHashTests.cpp
 )

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
