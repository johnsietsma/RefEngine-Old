cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

# gtest stomps the CRT settings, so I stomp the test executeables in the same way so that it links correctly.
# Stealing googles code from: https://code.humavips.eu/svn/naorsb/tags/paris/RSBImageConverter/3rdparty/gtest-1.5.0/CMakeLists.txt
if (MSVC)
  # For MSVC, CMake sets certain flags to defaults we want to override.
  # This replacement code is taken from sample in the CMake Wiki at
  # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
  foreach (flag_var
           CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
           CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    # In hermetic build environments, tests may not have access to MS runtime
    # DLLs, so this replaces /MD (CRT libraries in DLLs) with /MT (static CRT
    # libraries).
    string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
    # We prefer more strict warning checking for building Google Test.
    # Replaces /W3 with /W4 in defaults.
    string(REPLACE "/W3" "-W4" ${flag_var} "${${flag_var}}")
  endforeach()
endif()
# end google's stomping code.


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RefEngineTests Tests.cpp)

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
