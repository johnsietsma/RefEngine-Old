#pragma once

#include "AssetManager.h"
#include "FlyInput.h"
#include "RefEngine.h"


#include <memory>
#include <vector>

class FBXFile;
class SpinProcessor;

namespace reng {
	class AssetManager;
	class RefEngine;
}

class TestBed : public reng::RefEngine
{
public:
	TestBed();

private:
	void DoUpdate(double deltaTime) override;
	bool DoInit() override;

    void AddTexturedQuad( glm::vec3 pos );
    void AddSpinningTri( glm::vec3 pos );
    void AddVertexColoredCube( glm::vec3 pos );
    void AddLitCube( glm::vec3 pos );
    void AddFbxModel( glm::vec3 pos, const char* fbxPath );

    reng::AssetManager m_assetManager;
	reng::FlyInput m_flyInput;
};
