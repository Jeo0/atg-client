#include "core/guiApp.h"


int main() {

    // auto app = std::make_unique<Application>("ATG");
    // app->loop();
    GuiApp app;
    // initialize the window, opengl, imgui
    if (!app.Init(1280, 720, "My Awesome ImGui App")) {
        return -1;
    }
    app.Run();

    app.Shutdown();

    return 0;
}

