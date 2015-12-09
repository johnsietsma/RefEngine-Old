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

    reng::AssetManager m_assetManager;
	reng::FlyInput m_flyInput;
};
