#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

namespace reng {


class DebugComponent
{
public:
    virtual void DrawDebugUI() = 0;
};

}
