#pragma once

#ifdef GNM_PLATFORM_WINDOWS

extern Ganymede::Application *Ganymede::CreateApplication();

int main(int argc, char** argv) {
    Ganymede::Log::Init();

    GNM_PROFILE_BEGIN_SESSION("Startup", "GanymedeProfile-Startup.json");
    auto app = Ganymede::CreateApplication();
    GNM_PROFILE_END_SESSION();

    GNM_PROFILE_BEGIN_SESSION("Runtime", "GanymedeProfile-Runtime.json");
    app->Run();
    GNM_PROFILE_END_SESSION();
    
    GNM_PROFILE_BEGIN_SESSION("Shutdown", "GanymedeProfile-Shutdown.json");
    delete app;
    GNM_PROFILE_END_SESSION();
}

#endif