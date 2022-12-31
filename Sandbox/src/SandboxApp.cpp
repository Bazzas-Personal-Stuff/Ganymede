#include <Ganymede.h>
#include <Ganymede/Core/EntryPoint.h>
#include "Sandbox2D.h"

class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        PushLayer(new Sandbox2D());
    }

    virtual ~Sandbox() override = default;
};


Ganymede::Ref<Ganymede::Application> Ganymede::CreateApplication() {
    return Ganymede::Ref<Application>(new Sandbox());
}
