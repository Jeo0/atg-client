// #include "glad/glad.h"
// #include "opengltings/glHelper.h"
#include "core/guiApp.h"


int main() {
    // const char* vertShader = ShaderReader("shaders/default.vert").c_str();
    // GLuint verObj = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(verObj, 1, &vertShader, NULL);
    // glCompileShader(verObj);

    GuiApp app;
    // Initialize the window, OpenGL, and ImGui
    if (!app.Init(1280, 720, "My Awesome ImGui App")) {
        return -1;
    }

    // Run the main rendering loop
    app.Run();

    // Clean up resources
    app.Shutdown();

    return 0;
}

