#pragma once

#include "debug/DebugGUI_GLFW.h"
#include "debug/DebugUI_GLFW.cpp"

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

#include "RefEngine.h"

#include <memory>

namespace reng {


class DebugComponent : DrawComponent
{
public:
    virtual void DrawDebugUI(ComponentId componentId) = 0;

    DebugComponent() :
        m_pDebugGUI( std::make_shared<DebugGUI>() )
    {
        m_pDebugGUI->Init();
    }

    ~DebugComponent()
    {
        m_pDebugGUI->DeInit();
    }

    void Draw()
    {
        m_pDebugGUI->NewFrame();

        for (auto& pEntity : m_pRefEngine->GetEntities())
        {
            if (pEntity->HasDebugComponents() && m_pDebugGUI->StartEntity(pEntity->GetId(), pEntity->GetName())) {
                pEntity->DrawDebugUI(*GetComponentDatabase());
                m_pDebugGUI->EndEntity();
            }
        }

        m_pDebugGUI->Draw();

    }

private:
    std::shared_ptr<DebugGUI> m_pDebugGUI;

    std::shared_ptr<RefEngine> m_pRefEngine;

};

}
