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
	class Entity;
	class AABBGizmoProcessor;
	class PhysXProcessor;
	class PhysicsProcessor;
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
	std::vector<std::shared_ptr<reng::Entity>> m_entities;
	std::shared_ptr<SpinProcessor> m_spinProcessor;
	std::shared_ptr<reng::PhysXProcessor> m_physXProcessor;
	std::shared_ptr<reng::PhysicsProcessor> m_physicsProcessor;
	std::shared_ptr<reng::AABBGizmoProcessor> m_gizmoProcessor;
};
