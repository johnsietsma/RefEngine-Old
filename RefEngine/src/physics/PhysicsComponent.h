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

class RigidbodyComponent
{
public:
	RigidbodyComponent(float mass, const glm::vec3& velocity) :
		m_mass(mass),
		m_velocity(velocity)
	{}

	const glm::vec3& GetVelocity() const { return m_velocity; }

	void SetVelocity(const glm::vec3& velocity) { m_velocity = velocity;  }
	void ApplyForce(const glm::vec3& force) { m_velocity += force/m_mass; }

private:
	float m_mass;
	glm::vec3 m_velocity;
};

struct PhysicsComponent
{
	enum class GemometryType { None, Plane, Box, Sphere };

	PhysicsComponent(GemometryType a_geoType) :
		geometryType(a_geoType)
	{}

	GemometryType geometryType;
};


class PhysicsProcessor : public reng::Processor<PhysicsComponent, GameTime>
{
public:
	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager, GameTime& time) override;

private:
	glm::vec3 m_gravity{ 0, -9.8f, 0 };
};

}
