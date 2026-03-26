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

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) return false;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

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

std::string shadad(std::string p_file) {
    std::string e_source, e_line {};

    std::ifstream theFile(p_file);
    if(theFile.is_open()){
        while(std::getline(theFile, e_line)){
            e_source += e_line + "\n";
        }
        theFile.close();
    }
    else {
        std::cerr << "error opening file";
    }
    return e_source;
}

void GuiApp::Run() {
    const char* vertShader = shadad("src/shaders/default.vert").c_str();
    GLuint verObj = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(verObj, 1, &vertShader, NULL);
    glCompileShader(verObj);

    GLint success = 0;
    GLchar* log;
    char* msg = "asd";
    {
        glGetShaderiv(verObj, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(verObj, 512, NULL, log);
            printf(strcat(strcpy(msg, "Vertex Shader Failed to Compile!\n> OpenGL Error: "), log));
        }
    }

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
