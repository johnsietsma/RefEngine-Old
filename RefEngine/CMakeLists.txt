cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

IF(APPLE)
    SET(FBX_SDK_DIR "/Applications/Autodesk/FBX SDK/2015.1/" CACHE PATH "The location of the FBX SDK" )
ELSE(APPLE)
    SET(FBX_SDK_DIR "C:/Program Files/Autodesk/FBX/FBX SDK/2015.1/" CACHE PATH "The location of the FBX SDK" )
    SET(PHYSX_SDK_DIR "C:/Physx/" CACHE PATH "The location of the PhysX SDK" )
ENDIF()

IF(APPLE)
  SET(FBX_LIB_DIR ${FBX_SDK_DIR}/clang/)
ELSE(APPLE)
  SET(FBX_LIB_DIR ${FBX_SDK_DIR}/lib/vs2013/x86/)
  SET(PHYSX_LIB_DIR ${PHYSX_SDK_DIR}/Lib/vc12win32/)
  SET(PHYSX_INCLUDE_DIR ${PHYSX_SDK_DIR}/include CACHE STRING "PhysX header path")
  SET(PHYSX_BIN_DIR ${PHYSX_SDK_DIR}/bin CACHE STRING "PhysX dll path")
ENDIF()

include_directories(../dep/aieutilities)
include_directories(../dep/glm)
include_directories(../dep/glfw/include)
include_directories(${FBX_SDK_DIR}/include)
include_directories(${PHYSX_INCLUDE_DIR})
include_directories(../dep/FBXLoader)
include_directories(../dep/stb)
include_directories(src)

if (MSVC)
    option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON)
endif()


IF(APPLE)
    SET(GCC_CHAR_IS_UNSIGNED_CHAR "-funsigned-char")
    SET(STD_C11 "-std=c++11 -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
ENDIF (APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

add_definitions(-DGLM_SWIZZLE)

add_library(refeng
    ../Readme.md
    src/AssetManager.cpp
    src/AssetManager.h
    src/CachingFactory.h
    src/Camera.cpp
    src/Camera.h
    src/Color.cpp
    src/Color.h
    src/FlyInput.cpp
    src/FlyInput.h
    src/GameTime.h
	src/GizmosComponent.cpp
	src/GizmosComponent.h
    src/ReadMe.txt
    src/RefEngine.cpp
    src/RefEngine.h
    src/StronglyTyped.h
    src/targetver.h
    src/Transform.h
    src/types.h
    src/VariadicHash.cpp
    src/VariadicHash.h

    src/components/ComponentContainer.h
    src/components/ComponentManager.h
    src/components/ComponentManager.cpp
    src/components/Entity.h
    src/components/Entity.cpp
    src/components/EntityManager.cpp
    src/components/EntityManager.h
    src/components/Processor.h

    src/graphics/gl_core_4_1.c
    src/graphics/gl_core_4_1.h
    src/graphics/GLHelpers.cpp
    src/graphics/GLHelpers.h
    src/graphics/Material.cpp
    src/graphics/Material.h
    src/graphics/Mesh.cpp
    src/graphics/Mesh.h
    src/graphics/OpenGLRenderer.cpp
    src/graphics/OpenGLRenderer.h
    src/graphics/OpenGLTypes.h
    src/graphics/Prims.cpp
    src/graphics/Prims.h
    src/graphics/RenderProcessor.cpp
    src/graphics/RenderProcessor.h

    src/physics/PhysicsComponent.cpp
    src/physics/PhysicsComponent.h
    src/physics/PhysXComponent.cpp
    src/physics/PhysXComponent.h
	src/physics/PhysXTriggerShapeComponent.cpp
    src/physics/PhysXTriggerShapeComponent.h
	src/physics/PhysXGizmoComponent.cpp
    src/physics/PhysXGizmoComponent.h

    src/utils/memaligned.cpp
    src/utils/memaligned.h
    src/utils/pow2assert.cpp

    src/utils/pow2assert.h

    ../dep/FBXLoader/FBXFile.cpp
    ../dep/aieutilities/aie/Gizmos.cpp
)

source_group( Components src/components/ )
source_group( Graphics src/graphics/ )
source_group( Physics src/physics/ )
source_group( Utils src/utils/ )

target_include_directories (refeng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}\\src)
target_link_libraries(refeng glfw ${GLFW_LIBRARIES})

IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(CORE_VIDEO_LIBRARY CoreVideo)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   MARK_AS_ADVANCED (CARBON_LIBRARY CORE_VIDEO_LIBRARY COCOA_LIBRARY OpenGL_LIBRARY IOKIT_LIBRARY)
   SET(EXTRA_LIBS ${CARBON_LIBRARY} ${CORE_VIDEO_LIBRARY} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY})

   target_link_libraries(refeng ${FBX_LIB_DIR}libfbxsdk.a)
ELSE(APPLE)
   target_link_libraries(refeng opengl32.lib)

   target_link_libraries(refeng optimized ${PHYSX_LIB_DIR}PhysX3_x86.lib)
   target_link_libraries(refeng optimized ${PHYSX_LIB_DIR}PhysX3Common_x86.lib)
   target_link_libraries(refeng optimized ${PHYSX_LIB_DIR}PhysX3Extensions.lib)
   target_link_libraries(refeng optimized ${PHYSX_LIB_DIR}PhysXVisualDebuggerSDK.lib)

   target_link_libraries(refeng debug ${PHYSX_LIB_DIR}PhysX3DEBUG_x86.lib)
   target_link_libraries(refeng debug ${PHYSX_LIB_DIR}PhysX3CommonDEBUG_x86.lib)
   target_link_libraries(refeng debug ${PHYSX_LIB_DIR}PhysX3ExtensionsDEBUG.lib)
   target_link_libraries(refeng debug ${PHYSX_LIB_DIR}PhysXVisualDebuggerSDKDEBUG.lib)

   if (USE_MSVC_RUNTIME_LIBRARY_DLL)
     target_link_libraries(refeng optimized ${FBX_LIB_DIR}release/libfbxsdk-md.lib)
     target_link_libraries(refeng debug ${FBX_LIB_DIR}debug/libfbxsdk-md.lib)
   else (USE_MSVC_RUNTIME_LIBRARY_DLL)
       target_link_libraries(refeng optimized ${FBX_LIB_DIR}release/libfbxsdk-mt.lib)
     target_link_libraries(refeng debug ${FBX_LIB_DIR}debug/libfbxsdk-mt.lib)
   endif()
ENDIF (APPLE)

target_link_libraries(refeng ${EXTRA_LIBS})

