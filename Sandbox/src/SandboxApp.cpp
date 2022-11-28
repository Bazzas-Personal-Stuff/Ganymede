#include <Ganymede.h>

class ExampleLayer : public Ganymede::Layer {
public:
    ExampleLayer() : Layer("Example"){}

    void OnUpdate() override {
        GNM_INFO("ExampleLayer::Update");
    }

    void OnEvent(Ganymede::Event& event) override {
        GNM_TRACE("{0}", event);
    }
};


class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new Ganymede::ImGuiLayer());
    }
    ~Sandbox(){}
};

Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}