#include "core/guiApp.h"


int main() {

    // auto app = std::make_unique<Application>("ATG");
    // app->loop();
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

