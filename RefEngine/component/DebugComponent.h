#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

namespace reng {


class DebugComponent
{
public:
    virtual void DrawDebugUI() = 0;

    template<typename T>
    static void DebugProcessor(void* empty, ComponentContainer<T>& container)
    {
        for (auto& component : container) {
			component.DrawDebugUI();
        }
    }
};

}
