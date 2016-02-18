#pragma once

#include "entity/ComponentContainer.h"
#include "entity/ComponentDatabase.h"

namespace reng {


// A component that has its draw function called every frame.
// Override to create your own draw component.
class DrawComponent
{
public:
    virtual void Draw(ComponentDatabase& database) = 0;

    // Updates all the components in the container.
    template<typename T>
    static void DrawProcessor(ComponentContainer<T>& container, ComponentDatabase& database )
    {
        for (auto& component : container) {
            component.Draw(database);
        }
    }
};

}
