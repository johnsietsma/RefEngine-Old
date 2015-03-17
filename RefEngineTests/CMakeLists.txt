cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

set(CMAKE_CXX_FLAGS "-g -Wall")


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RefEngineTests Tests.cpp)

target_link_libraries(RefEngineTests gtest gtest_main)
target_link_libraries(RefEngineTests refeng)

add_test(
    NAME MethodBarDoesAbc
    COMMAND RefEngineTest)
