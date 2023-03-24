#include <Ganymede.h>
#include <Ganymede/Core/EntryPoint.h>
#include "Sandbox2D.h"
#include "SandboxDX2D.h"

class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        switch(Ganymede::Renderer::GetAPI()) {
        case Ganymede::RendererAPI::API::DX11:
            PushLayer(new SandboxDX2D());
            break;
        case Ganymede::RendererAPI::API::OpenGL: ;
            PushLayer(new Sandbox2D());
            break;
        default:
            GNM_ASSERT(false, "Unknown Renderer API");
        }
    }

    virtual ~Sandbox() override = default;
};


Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}
