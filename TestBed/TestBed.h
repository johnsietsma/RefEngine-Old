#pragma once

#include "AssetManager.h"
#include "RefEngine.h"

#include <memory>
#include <vector>

class FBXFile;
namespace reng {
	class AssetManager;
	class Entity;
	class RefEngine;
}

class TestBed
{
public:
	TestBed();

	bool Init();

	void Run();

private:
    std::unique_ptr<reng::AssetManager> m_pAssetManager;
	std::unique_ptr<reng::RefEngine> m_pRefEngine;

	std::vector<std::shared_ptr<reng::Entity>> m_entities;
};
