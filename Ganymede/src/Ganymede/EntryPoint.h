#pragma once

#ifdef GNM_PLATFORM_WINDOWS

extern Ganymede::Ref<Ganymede::Application> Ganymede::CreateApplication();

int main(int argc, char** argv) {
    Ganymede::Log::Init();

    auto app = Ganymede::CreateApplication();
    app->Run();
    // delete app;
}

#endif