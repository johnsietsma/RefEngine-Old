cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(../dep/aieutilities)
include_directories(../dep/glm)
include_directories(../dep/glfw/include)
include_directories(../dep/fbx/include)
include_directories(../dep/FBXLoader)
include_directories(../dep/stb)
include_directories(src)

if (MSVC)
    option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON)
endif()


IF(APPLE)
    SET(GCC_CHAR_IS_UNSIGNED_CHAR "-funsigned-char")
    SET(STD_C11 "-std=c++0x")
ENDIF (APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

add_library(refeng
	../Readme.md
    src/AssetManager.cpp
    src/AssetManager.h
	src/CachingFactory.h
    src/Camera.cpp
    src/Camera.h
    src/Color.cpp
    src/Color.h
    src/Controller.cpp
    src/Controller.h
    src/ComponentManager.cpp
    src/ComponentManager.h
    src/EntityManager.cpp
    src/EntityManager.h
    src/GameObject.cpp
    src/GameObject.h
    src/gl_core_4_1.c
    src/gl_core_4_1.h
    src/GLHelpers.cpp
    src/GLHelpers.h
    src/memaligned.cpp
    src/memaligned.h
    src/Material.cpp
    src/Material.h
	src/Mesh.h
	src/Mesh.cpp
    src/OpenGLRenderer.h
    src/OpenGLRenderer.cpp
    src/OpenGLTypes.h
    src/pow2assert.cpp
    src/pow2assert.h
    src/Prims.cpp
    src/Prims.h
	src/processor.h
    src/RefEngine.h
    src/RefEngine.cpp
    src/Renderable.cpp
    src/Renderable.h
    src/Renderer.cpp
    src/Renderer.h
    src/SpinController.cpp
    src/SpinController.h
	src/Time.h
	src/Transform.h
    src/types.h
	src/VariadicHash.cpp
	src/VariadicHash.h
    ../dep/FBXLoader/FBXFile.cpp
    ../dep/aieutilities/aie/Gizmos.cpp
)

target_include_directories (refeng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}\\src)

IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(CORE_VIDEO_LIBRARY CoreVideo)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   MARK_AS_ADVANCED (CARBON_LIBRARY CORE_VIDEO_LIBRARY COCOA_LIBRARY OpenGL_LIBRARY IOKIT_LIBRARY)
   SET(EXTRA_LIBS ${CARBON_LIBRARY} ${CORE_VIDEO_LIBRARY} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY})

   target_link_libraries(refeng ${CMAKE_SOURCE_DIR}/dep/fbx/libfbxsdk.a)
   target_link_libraries(refeng glfw ${GLFW_LIBRARIES})
ELSE(APPLE)
   target_link_libraries(refeng opengl32.lib)
   target_link_libraries(refeng glfw ${GLFW_LIBRARIES})
   if (USE_MSVC_RUNTIME_LIBRARY_DLL)
	   target_link_libraries(refeng optimized ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/release/libfbxsdk-md.lib)
	   target_link_libraries(refeng debug ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/debug/libfbxsdk-md.lib)
   else (USE_MSVC_RUNTIME_LIBRARY_DLL)
   	   target_link_libraries(refeng optimized ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/release/libfbxsdk-mt.lib)
	   target_link_libraries(refeng debug ${CMAKE_SOURCE_DIR}/dep/fbx/vs2013/x86/debug/libfbxsdk-mt.lib)
   endif()
ENDIF (APPLE)

target_link_libraries(refeng ${EXTRA_LIBS})
