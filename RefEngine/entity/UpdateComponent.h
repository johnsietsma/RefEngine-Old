#pragma once

#include "entity/Component.h"

namespace reng {


// A component that has it's update function called every frame.
// Override to create your own updateable component.
class UpdateComponent : public IComponent
{
public:
    virtual void Update(double deltaTime) = 0;

    // Updates all the components in the container.
    template<typename T>
    static void UpdateProcessor(double deltaTime, ComponentContainer<T>& container)
    {
        for (auto& component : container) {
            component.Update(deltaTime);
        }
    }
};

}
