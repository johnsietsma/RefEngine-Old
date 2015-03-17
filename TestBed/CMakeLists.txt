cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

IF(APPLE)
    SET(GCC_CHAR_IS_UNSIGNED_CHAR "-funsigned-char")
    SET(STD_C11 "-std=c++0x")
ELSE(APPLE)
ENDIF (APPLE)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

add_executable(TestBed
    Main.cpp
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


IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(CORE_VIDEO_LIBRARY CoreVideo)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   MARK_AS_ADVANCED (CARBON_LIBRARY CORE_VIDEO_LIBRARY COCOA_LIBRARY OpenGL_LIBRARY IOKIT_LIBRARY)
   SET(EXTRA_LIBS ${CARBON_LIBRARY} ${CORE_VIDEO_LIBRARY} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY})

   target_link_libraries(TestBed ${CMAKE_SOURCE_DIR}/dep/fbx/libfbxsdk.a)
   target_link_libraries(TestBed glfw ${GLFW_LIBRARIES})
ELSE(APPLE)
   target_link_libraries(TestBed opengl32.lib)
   target_link_libraries(TestBed glfw ${GLFW_LIBRARIES})
   target_link_libraries(TestBed optimized ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/release/libfbxsdk-md.lib)
   target_link_libraries(TestBed debug ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/debug/libfbxsdk-md.lib)
ENDIF (APPLE)

target_link_libraries(TestBed ${EXTRA_LIBS})
