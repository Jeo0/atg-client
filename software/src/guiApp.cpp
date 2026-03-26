#include "glad/glad.h"
#include "core/guiApp.h"
#include "opengltings/glHelper.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>

bool GuiApp::Init(int width, int height, const char* title) {
    // 1. Setup GLFW
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // setup window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) return false;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

	gladLoadGL(); // initialize glad

    // 2. Setup Dear ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // 3. Setup Platform/Renderer Backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");


    return true;
}


void GuiApp::Run() {
    // -----------------
    // trial
    std::string sourceFile = ShaderReader("src/shaders/default.vert");
    const char* vertShader = sourceFile.c_str();
    GLuint verObj = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(verObj, 1, &vertShader, NULL);
    glCompileShader(verObj);

    GLint success = 0;
    short int logSize = 512;
    GLchar log[logSize];
    glGetShaderiv(verObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(verObj, logSize, NULL, log);
        std::cerr << "Vertex Shader Failed to Compile!\n> OpenGL Error: " << log << std::endl;
    }
    // -----------------

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call your custom UI code
        RenderUI();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void GuiApp::RenderUI() {
    // THIS is where you put your actual application logic!
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is a beautifully architected application.");


    ImGui::End();
}

void GuiApp::Shutdown() {
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}
