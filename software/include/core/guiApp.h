#pragma once
#include <glfw/glfw3.h>

class GuiApp {
public:
    GuiApp() = default;
    ~GuiApp() = default;

    bool Init(int width, int height, const char* title);
    void Run();
    void Shutdown();

private:
    void RenderUI(); // Put your actual ImGui window code here

    GLFWwindow* window = nullptr;
};
