#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "Transform.h"

#include <glm/fwd.hpp>

namespace reng {

class GameTime;


struct Geometry
{};

struct Plane {};
struct Box {};
struct Sphere {};

struct RigidbodyComponent
{
	RigidbodyComponent(float a_mass, const glm::vec3& a_velocity) :
		mass(a_mass),
		velocity(a_velocity)
	{}

	float mass;
	glm::vec3 velocity;
};

struct PhysicsComponent
{
	enum class GemometryType { None, Plane, Box, Sphere };

	PhysicsComponent(GemometryType a_geoType, bool a_isStatic=false) :
		geometryType(a_geoType),
		isStatic(a_isStatic)
	{}

	GemometryType geometryType;
	bool isStatic;
};


class PhysicsProcessor : public reng::Processor<PhysicsComponent, GameTime>
{
public:
	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager, GameTime& time) override;

private:
	float m_gravity = -9.8f;
};

}
