#pragma once


#ifdef GNM_PLATFORM_WINDOWS

extern Ganymede::Application* Ganymede::CreateApplication();

inline int main(int argc, char** argv) {
    auto app = Ganymede::CreateApplication();
    app->Run();
    delete app;
}

#endif