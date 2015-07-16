cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

IF(APPLE)
    SET(GCC_CHAR_IS_UNSIGNED_CHAR "-funsigned-char")
    SET(STD_C11 "-std=c++0x")
ELSE(APPLE)
ENDIF (APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

include_directories(../dep/glm)
include_directories(../dep/FBXLoader)

add_executable(TestBed
    Main.cpp
	TestBed.cpp
	Testbed.h
    data/shaders/default.vert
    data/shaders/passthrough.vert
    data/shaders/diffuse.frag
    data/shaders/red.frag
    data/shaders/white.frag
)

target_link_libraries(TestBed refeng)

# ---- Put the shaders in a folder group ----
FILE(GLOB frag_shaders data/shaders/*.*)
source_group(data\\shaders FILES ${frag_shaders})

add_custom_command(TARGET TestBed POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:TestBed>/../data COMMENT "Copying data to output directory"
)
