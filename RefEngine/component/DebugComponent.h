#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

namespace reng {


class DebugComponent
{
public:
    //virtual void AddDebugVars(TwBar* pBar) = 0;

    template<typename T>
    static void AddDebugVarsProcessor(ComponentContainer<T>& container)
    {
        for (auto& component : container) {
            //component.AddDebugVars( pBar );
        }
    }
};

}
