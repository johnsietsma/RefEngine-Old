cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

IF(APPLE)
    SET(FBX_SDK_DIR "/Applications/Autodesk/FBX SDK/2015.1/" CACHE PATH "The location of the FBX SDK" )
ELSE(APPLE)
    SET(FBX_SDK_DIR "C:/Program Files/Autodesk/FBX/FBX SDK/2015.1/" CACHE PATH "The location of the FBX SDK" )
    SET(PHYSX_SDK_DIR "C:/Physx/" CACHE PATH "The location of the PhysX SDK" )
ENDIF()

IF(APPLE)
  SET(FBX_LIB_DIR ${FBX_SDK_DIR}/lib/clang/)
ELSE(APPLE)
  SET(FBX_LIB_DIR ${FBX_SDK_DIR}/lib/vs2013/x86/)
  SET(PHYSX_LIB_DIR ${PHYSX_SDK_DIR}/Lib/vc12win32/)
  SET(PHYSX_INCLUDE_DIR ${PHYSX_SDK_DIR}/include CACHE STRING "PhysX header path")
  SET(PHYSX_BIN_DIR ${PHYSX_SDK_DIR}/bin CACHE STRING "PhysX dll path")
ENDIF()

include_directories(../dep/aieutilities)
include_directories(../dep/glm)
include_directories(../dep/GLFW/include)
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
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
ENDIF (APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C11}")

add_definitions(-DGLM_SWIZZLE)

add_library(refeng
    ../Readme.md
    AssetManager.cpp
    AssetManager.h
    CachingFactory.h
    Camera.cpp
    Camera.h
    Color.cpp
    Color.h
    FlyInput.cpp
    FlyInput.h
    GameTime.h
    make_unique.h
    MaterialManager.h
    MaterialManager.cpp
    ReadMe.txt
    RefEngine.cpp
    RefEngine.h
    StronglyTyped.h
    targetver.h
    Transform.cpp
    Transform.h
    types.h
    VariadicHash.cpp
    VariadicHash.h

    component/CameraComponent.h
    component/FlyInputComponent.h
    component/LightComponent.h
    component/RenderableComponent.h
    component/RenderableComponent.cpp
    component/TransformComponent.h
    component/UpdateComponent.h


    entity/Component.h
    entity/ComponentContainer.h
    entity/ComponentDatabase.h
    entity/ComponentHandle.h
    entity/ComponentProcessor.h
    entity/ComponentProcessor.cpp
    entity/Entity.h

    graphics/Primitive.h
    graphics/Primitive.cpp
    graphics/gl_core_4_4.c
    graphics/gl_core_4_4.h
    graphics/GLEnum.h
    graphics/GLHelpers.cpp
    graphics/GLHelpers.h
    graphics/GLProgram.h
    graphics/GLTypes.h
    graphics/Material.cpp
    graphics/Material.h
    graphics/Mesh.cpp
    graphics/Mesh.h
    graphics/OpenGLRenderer.cpp
    graphics/OpenGLRenderer.h
    graphics/Prims.cpp
    graphics/Prims.h
    graphics/Texture.h

    utils/memaligned.cpp
    utils/memaligned.h
    utils/pow2assert.cpp
    utils/pow2assert.h

    ../dep/FBXLoader/FBXFile.cpp
    ../dep/aieutilities/aie/Gizmos.cpp
)

source_group( Components components/ )
source_group( Entity entity/ )
source_group( Graphics graphics/ )
source_group( Utils utils/ )

target_include_directories (refeng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}\\)
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

   target_link_libraries(refeng optimized ${FBX_LIB_DIR}release/libfbxsdk.a)
   target_link_libraries(refeng debug ${FBX_LIB_DIR}debug/libfbxsdk.a)
ELSE(APPLE)
   target_link_libraries(refeng opengl32.lib)

   if (USE_MSVC_RUNTIME_LIBRARY_DLL)
     target_link_libraries(refeng optimized ${FBX_LIB_DIR}release/libfbxsdk-md.lib)
     target_link_libraries(refeng debug ${FBX_LIB_DIR}debug/libfbxsdk-md.lib)
   else (USE_MSVC_RUNTIME_LIBRARY_DLL)
       target_link_libraries(refeng optimized ${FBX_LIB_DIR}release/libfbxsdk-mt.lib)
     target_link_libraries(refeng debug ${FBX_LIB_DIR}debug/libfbxsdk-mt.lib)
   endif()
ENDIF (APPLE)

target_link_libraries(refeng ${EXTRA_LIBS})

