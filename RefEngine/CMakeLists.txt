cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(../dep/aieutilities)
include_directories(../dep/glm)
include_directories(../dep/glfw/include)
include_directories(../dep/fbx/include)
include_directories(../dep/FBXLoader)
include_directories(../dep/stb)
include_directories(src)


IF(APPLE)
    SET(GCC_CHAR_IS_UNSIGNED_CHAR "-funsigned-char")
    SET(STD_C11 "-std=c++0x")
ELSE(APPLE)
ENDIF (APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")


add_library(refeng
    src/AssetContainer.cpp
    src/AssetContainer.h
    src/Buffer.cpp
    src/Buffer.h
    src/Camera.cpp
    src/Camera.h
    src/Color.cpp
    src/Color.h
    src/CachingFactory.h
    src/Controller.cpp
    src/Controller.h
    src/ComponentContainer.cpp
    src/ComponentContainer.h
    src/Components.cpp
    src/Components.h
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
    src/MeshRenderer.cpp
    src/MeshRenderer.h
    src/Material.cpp
    src/Material.h
    src/OpenGLTypes.cpp
    src/OpenGLTypes.h
    src/pow2assert.cpp
    src/pow2assert.h
    src/Prims.cpp
    src/Prims.h
    src/RefEngine.h
    src/RefEngine.cpp
    src/Renderable.cpp
    src/Renderable.h
    src/Renderer.cpp
    src/Renderer.h
    src/SpinController.cpp
    src/SpinController.h
    src/types.h
    ../dep/FBXLoader/FBXFile.cpp
    ../dep/aieutilities/aie/Gizmos.cpp
)

target_include_directories (refeng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}\\src)

