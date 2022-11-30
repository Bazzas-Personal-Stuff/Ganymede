#include <Ganymede.h>

class ExampleLayer : public Ganymede::Layer {
public:
    ExampleLayer() : Layer("Example"){}

    void OnUpdate() override {
        if(Ganymede::Input::IsKeyPressed(GNM_KEY_SPACE)) {
            GNM_LOG("Space has been pressed!");
        }
    }

    void OnEvent(Ganymede::Event& event) override {
    }
};


class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox(){}
};

Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}