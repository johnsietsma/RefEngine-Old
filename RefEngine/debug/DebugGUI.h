#pragma once

struct GLFWwindow;
struct CTwBar;
typedef struct CTwBar TwBar;

namespace reng 
{

class DebugGUI
{
public:
    void Init(GLFWwindow* pWindow);
    void DeInit();

    void Draw();

private:
    TwBar *m_bar;
};

}
