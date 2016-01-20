#pragma once

#include "RefEngine.h"

#include <memory>

struct GLFWwindow;

namespace reng {

class RefEngine;

class WindowGLFW
{
public:
    WindowGLFW();
    ~WindowGLFW();

    bool Init();
    void Run();

    GLFWwindow* GetWindow() { return m_pWindow; }
    RefEngine* GetEngine() { return m_pRefEngine.get(); }

private:

    void Destroy();

    bool m_isValid;
    GLFWwindow* m_pWindow;
    std::unique_ptr<RefEngine> m_pRefEngine;
};

}
