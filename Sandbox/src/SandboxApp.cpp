#include <Ganymede.h>
#include <cstdio>

class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        GNM_INFO("Hello, world!");
    }
    ~Sandbox(){}
};

Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}