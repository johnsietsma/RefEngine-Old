#pragma once

#include "AssetManager.h"
#include "RefEngine.h"

#include <memory>
#include <vector>

class FBXFile;
class SpinProcessor;

namespace reng {
	class AssetManager;
	class Entity;
	class RefEngine;
}

class TestBed : public reng::RefEngine
{
public:
	TestBed();

private:
	void DoUpdate(double deltaTime) override;
	bool DoInit() override;

    std::unique_ptr<reng::AssetManager> m_pAssetManager;
	std::vector<std::shared_ptr<reng::Entity>> m_entities;
	std::shared_ptr<SpinProcessor> m_spinProcessor;
};
