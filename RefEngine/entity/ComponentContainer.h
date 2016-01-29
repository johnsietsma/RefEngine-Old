#pragma once

#include "entity/Component.h"

#include "utils/pow2assert.h"

#include <functional>
#include <vector>

namespace reng 
{

// Generic parent class to allow homogenous storage of component containers.
class IComponentContainer
{
public:
    virtual ~IComponentContainer() = default;

	virtual void* GetComponentPointer(ComponentId id) = 0;

};

// A container for one component type
template<typename T>
class ComponentContainer : public IComponentContainer
{
public:
    ~ComponentContainer<T>() override = default;

	void* GetComponentPointer(ComponentId id) override
	{
		POW2_ASSERT(id >= 0);
		POW2_ASSERT(id < m_components.size());
		return &m_components[id];
	}

	T& GetComponent(ComponentId id) {
		POW2_ASSERT(id >= 0);
		POW2_ASSERT(id < m_components.size());
		return m_components[id];
	}

    ComponentId EmplaceComponent() {
        m_components.emplace_back();
        return m_components.size() - 1;
    }

    template<class ...TArgs>
    ComponentId EmplaceComponent(TArgs... args) {
        m_components.emplace_back(args...);
        return m_components.size() - 1;
    }

    // Supporting ranged for loops.
    typename std::vector<T>::iterator begin() { return m_components.begin(); }
    typename std::vector<T>::iterator end() { return m_components.end(); }

private:
    std::vector<T> m_components;
};

}
