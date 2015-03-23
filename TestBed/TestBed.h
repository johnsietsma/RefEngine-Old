#pragma once

#include <memory>

class FBXFile;
namespace reng {
	class AssetManager;
	class RefEngine;
}

class TestBed 
{
public:
	TestBed();

	bool Init();

	void Run();

private:
	std::unique_ptr<reng::RefEngine> m_pRefEngine;
	std::unique_ptr<reng::AssetManager> m_pAssetManager;
	std::shared_ptr<FBXFile> m_fbx;

};
