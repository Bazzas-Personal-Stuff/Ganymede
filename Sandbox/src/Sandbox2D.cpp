#include "Sandbox2D.h"

#include "Ganymede/Events/KeyEvent.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
    m_CameraController(16.0f/9.0f){

    m_Texture = Ganymede::Texture2D::Create("assets/textures/dude.png");
}

void Sandbox2D::OnAttach() {
    Layer::OnAttach();
}

void Sandbox2D::OnDetach() {
    Layer::OnDetach();
}

void Sandbox2D::OnUpdate() {
    m_CameraController.OnUpdate();
    
    Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Ganymede::RenderCommand::Clear();

    Ganymede::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Ganymede::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, m_FlatColor);
    Ganymede::Renderer2D::DrawQuad({0.5f, 0.5f, -0.1f}, {1.0f, 1.0f}, m_FlatColor, m_Texture);
    Ganymede::Renderer2D::EndScene();

    // -----------------------------
    
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_FlatColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Ganymede::Event& e) {
    // Ganymede::EventDispatcher dispatcher(e);
    m_CameraController.OnEvent(e);        
}

bool Sandbox2D::OnMouseMovedEvent(Ganymede::MouseMovedEvent& event) {
    // m_Camera.SetPosition({ m_CameraPosition + mousePos, 0.0f});

    return false;
}

bool Sandbox2D::OnKeyEvent(Ganymede::KeyEvent& event) {
    return false;
}



