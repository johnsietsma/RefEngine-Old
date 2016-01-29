#pragma once

#include "entity/Component.h"

namespace reng
{

// Allows retrieval of a Component from a container.
// Components may move in memory, this allows safe Component access.
struct ComponentHandle
{
    ComponentHandle(ComponentTypeId a_typeId, ComponentId a_id) :
        typeId(a_typeId),
        id(a_id)
    {}

	ComponentTypeId typeId;
    ComponentId id;
};

}