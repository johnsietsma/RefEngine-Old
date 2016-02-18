#pragma once

#include "debug/DebugGUI_GLFW.h"

#include "entity/Component.h"
#include "entity/ComponentContainer.h"

#include "RefEngine.h"

#include <memory>

namespace reng {


class DebugUIComponent : DrawComponent
{
public:
    DebugUIComponent(RefEngine* pRefEngine, GLFWwindow* pWindow ) :
        m_pDebugGUI( std::make_shared<DebugGUI>() ),
        m_pRefEngine( pRefEngine )
    {
        m_pDebugGUI->Init(pWindow);
    }

    ~DebugUIComponent()
    {
        m_pDebugGUI->DeInit();
    }

    void Draw(ComponentDatabase& database) override
    {
        m_pDebugGUI->NewFrame();

        for (auto& pEntity : m_pRefEngine->GetEntities())
        {
            if (pEntity->HasDebugComponents() && m_pDebugGUI->StartEntity(pEntity->GetId(), pEntity->GetName())) {
                pEntity->DrawDebugUI(database);
                m_pDebugGUI->EndEntity();
            }
        }

        m_pDebugGUI->Draw();

    }

private:
    std::shared_ptr<DebugGUI> m_pDebugGUI;
    RefEngine* m_pRefEngine;

};

}
