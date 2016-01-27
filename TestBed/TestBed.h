#pragma once

#include "RefEngWindowGLFW.h"

#include <memory>

namespace reng {
    class AssetManager;
    class RefEngine;
    class DebugGUI;
}

class TestBed
{
public:
	TestBed();

    bool Init();
    void Run();

private:
    void AddTexturedQuad( glm::vec3 pos );
    void AddSpinningTri( glm::vec3 pos );
    void AddVertexColoredCube( glm::vec3 pos );
    void AddLitCube( glm::vec3 pos );
    void AddFbxModel( glm::vec3 pos, const char* fbxPath );

    std::unique_ptr<reng::RefEngWindowGLFW> m_pWindow;
    reng::RefEngine* m_pEngine;
};
