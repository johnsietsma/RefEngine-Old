#pragma once

#include "entity/ComponentContainer.h"
#include "entity/ComponentDatabase.h"

namespace reng {


// A component that has its update function called every frame.
// Override to create your own updateable component.
class UpdateComponent
{
public:
    virtual void Update(double deltaTime, ComponentDatabase& database) = 0;

    // Updates all the components in the container.
    template<typename T>
    static void UpdateProcessor(double deltaTime, ComponentContainer<T>& container, ComponentDatabase& database )
    {
        for (auto& component : container) {
            component.Update(deltaTime, database);
        }
    }
};

}
