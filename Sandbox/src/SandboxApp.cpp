#include <Ganymede.h>
#include <cstdio>

class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        std::printf("Hello, world\n");
    }
    ~Sandbox(){}
};

Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}