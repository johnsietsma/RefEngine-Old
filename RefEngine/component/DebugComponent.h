#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

typedef struct CTwBar TwBar;

namespace reng {


class DebugComponent
{
public:
    virtual void AddDebugVars(TwBar* pBar) = 0;

    template<typename T>
    static void AddDebugVarsProcessor(TwBar* pBar, ComponentContainer<T>& container)
    {
        for (auto& component : container) {
            component.AddDebugVars( pBar );
        }
    }
};

}
