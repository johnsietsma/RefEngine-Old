cmake_minimum_required(VERSION 2.8)

#project(RefEngineTests)

enable_testing()
set(gtest_force_shared_crt ON)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../dep/glm)

add_executable(RefEngineTests
    CachingFactoryTests.cpp
    FileLoadPerfTests.cpp
    VariadicHashTests.cpp
 )

IF(APPLE)
	# Fix for Macs looking for .dylib
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    SET(STD_C11 "-std=c++11 -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
ENDIF(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

target_link_libraries(RefEngineTests gtest gtest_main)

target_link_libraries(RefEngineTests refeng)

add_test(
    NAME MethodBarDoesAbc
    COMMAND RefEngineTest)

IF(APPLE)
set(TARGET_ASSETS_DIR $<TARGET_FILE_DIR:RefEngineTests>/assets)
ELSE(APPLE)
set(TARGET_ASSETS_DIR $<TARGET_FILE_DIR:RefEngineTests>/../assets)
ENDIF (APPLE)


add_custom_command(TARGET RefEngineTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${TARGET_ASSETS_DIR} COMMENT "Copying assets to output directory."
)

