#pragma once

#include "Components/Processor.h"

#include "components/Entity.h"
#include "components/ComponentManager.h"
#include "Transform.h"

#include <glm/fwd.hpp>

namespace reng {

class GameTime;


struct GizmosComponent
{
};

struct AABBGizmoComponent
{
	AABBGizmoComponent( glm::vec3 a_extents, glm::vec4 a_color) :
		extents(a_extents),
		color(a_color)
	{
		int i = 0;
	}

	glm::vec3 extents;
	glm::vec4 color;
};


class AABBGizmoProcessor : public reng::Processor<AABBGizmoComponent>
{
public:
	virtual void DoProcess(const std::vector<reng::EntityId>& entityIds, reng::ComponentManager& componentManager) override;
};

}
