#pragma once

#include "RefEngine.h"

#include <memory>

struct GLFWwindow;

namespace reng {

class DebugGUI;
class RefEngine;

class RefEngWindowGLFW
{
public:
    RefEngWindowGLFW();
    ~RefEngWindowGLFW();

    bool Init();
    void Run();

    GLFWwindow* GetWindow() { return m_pWindow; }
    RefEngine* GetEngine() { return m_pRefEngine.get(); }

private:

    void Destroy();

    bool m_isValid;
    GLFWwindow* m_pWindow;
    std::unique_ptr<RefEngine> m_pRefEngine;
    std::unique_ptr<reng::DebugGUI> m_pDebugGUI;
};

}
