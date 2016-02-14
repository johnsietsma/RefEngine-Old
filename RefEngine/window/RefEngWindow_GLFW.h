#pragma once

#include "RefEngine.h"

#include "glm/vec2.hpp"

#include <memory>

struct GLFWwindow;

namespace reng {

class RefEngine;

class RefEngWindow
{
public:
    RefEngWindowGLFW();
    ~RefEngWindowGLFW();

    bool Init();
    void Run();

    GLFWwindow* GetWindow() { return m_pWindow; }
    RefEngine* GetEngine() { return m_pRefEngine.get(); }

	glm::vec2 GetSize() const;

private:

    void Destroy();

    bool m_isValid;
    GLFWwindow* m_pWindow;
    std::unique_ptr<RefEngine> m_pRefEngine;
};

}
