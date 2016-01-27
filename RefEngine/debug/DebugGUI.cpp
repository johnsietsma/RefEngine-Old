#include "DebugGUI.h"

#include "AntTweakBar.h"

#include "GLFW/glfw3.h"


using namespace reng;

void OnMouseButton(GLFWwindow*, int b, int a, int m) {
    TwEventMouseButtonGLFW(b, a);
}
void OnMousePosition(GLFWwindow*, double x, double y) {
    TwEventMousePosGLFW((int)x, (int)y);
}
void OnMouseScroll(GLFWwindow*, double x, double y) {
    TwEventMouseWheelGLFW((int)y);
}
void OnKey(GLFWwindow*, int k, int s, int a, int m) {
    TwEventKeyGLFW(k, a);
}
void OnChar(GLFWwindow*, unsigned int c) {
    TwEventCharGLFW(c, GLFW_PRESS);
}
void OnWindowResize(GLFWwindow*, int w, int h) {
    TwWindowSize(w, h);
    glViewport(0, 0, w, h);
}

void DebugGUI::Init(GLFWwindow* pWindow)
{
    TwInit(TW_OPENGL_CORE, NULL);

    int width, height;
    glfwGetWindowSize(pWindow, &width, &height);

    TwWindowSize(width, height);

    m_bar = TwNewBar("TwBar");

    // Set GLFW event callbacks
    // - Redirect window size changes to the callback function WindowSizeCB
    glfwSetWindowSizeCallback(pWindow, OnWindowResize);
    glfwSetMouseButtonCallback(pWindow, OnMouseButton);
    glfwSetCursorPosCallback(pWindow, OnMousePosition);
    glfwSetScrollCallback(pWindow, OnMouseScroll);
    glfwSetKeyCallback(pWindow, OnKey);
    glfwSetCharCallback(pWindow, OnChar);
}

void DebugGUI::DeInit()
{
    TwTerminate();
}

void DebugGUI::Draw()
{
    TwDraw();
}
