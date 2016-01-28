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
	TestBed.h
    ${ASSET_FILES}
)

source_group( Assets assets/ )

target_link_libraries(TestBed refeng)

# ---- Put the shaders in a folder group ----
FILE(GLOB frag_shaders data/shaders/*.*)
source_group(data\\shaders FILES ${frag_shaders})

IF(APPLE)
	set(TARGET_ASSETS_DIR $<TARGET_FILE_DIR:TestBed>/assets)
ELSE(APPLE)
	set(TARGET_ASSETS_DIR $<TARGET_FILE_DIR:TestBed>/../assets)
ENDIF (APPLE)


add_custom_command(TARGET TestBed POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${TARGET_ASSETS_DIR} COMMENT "Copying assets to output directory."
)
 