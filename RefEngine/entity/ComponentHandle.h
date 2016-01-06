#pragma once

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

namespace reng
{

// Allows retrieval of a Component from a container.
// Components may move in memory, this allows safe Component access.
template<typename T>
class ComponentHandle
{
public:
    ComponentHandle(ComponentContainer<T>& a_container, ComponentId a_id) :
        m_container(a_container),
        m_id(a_id)
    {}

    T& GetComponent() { return m_container.GetComponent(m_id); }
    const T& GetComponent() const { return m_container.GetComponent(m_id); }

private:
    ComponentContainer<T>& m_container;
    ComponentId m_id;
};

}