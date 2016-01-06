#pragma once

#include <typeindex>

namespace reng {

typedef size_t ComponentId;
typedef std::type_index ComponentTypeId;


class IComponent
{
public:
    virtual ~IComponent() {};
};

class Component 
{
public:
    Component() = delete;

    template<typename T>
    static ComponentTypeId GetTypeId() { return std::type_index(typeid(T)); }
};

}