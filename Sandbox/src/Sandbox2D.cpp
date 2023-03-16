#include "Sandbox2D.h"

#include "Ganymede/Events/KeyEvent.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
    m_CameraController(16.0f/9.0f){

    m_Texture = Ganymede::Texture2D::Create("assets/textures/dude.png");
    m_DudeSprite = Ganymede::SpriteData();
    m_DudeSprite.Texture = m_Texture;
}

void Sandbox2D::OnAttach() {
    GNM_PROFILE_FUNCTION();
    
    Layer::OnAttach();
}

void Sandbox2D::OnDetach() {
    GNM_PROFILE_FUNCTION();
    
    Layer::OnDetach();
}

void Sandbox2D::OnUpdate() {
    GNM_PROFILE_FUNCTION();

    m_CameraController.OnUpdate();

    {
        GNM_PROFILE_SCOPE("Renderer Prep");
        Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Ganymede::RenderCommand::Clear();
    }

    {
        GNM_PROFILE_SCOPE("Renderer Draw");
        Ganymede::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Ganymede::Renderer2D::Fill({0.8f, 0.5f, 0.5f, 1.0f});
        Ganymede::Renderer2D::Rect({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        Ganymede::Renderer2D::Fill(m_FlatColor);
        Ganymede::Renderer2D::Rect({0.5f, 0.5f, 0.0f}, {0.5f, 0.5f}, glm::radians(45.0f));
        Ganymede::Renderer2D::Rect({-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f});

        Ganymede::Renderer2D::Sprite({-1.0f, -1.0f, -0.5f}, {1.0f, 1.0f}, m_DudeSprite);
        Ganymede::Renderer2D::EndScene();
    }
    // -----------------------------
    
}

void Sandbox2D::OnImGuiRender() {
    GNM_PROFILE_FUNCTION();
    
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_FlatColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Ganymede::Event& e) {
    GNM_PROFILE_FUNCTION();
    
    // Ganymede::EventDispatcher dispatcher(e);
    m_CameraController.OnEvent(e);        
}

bool Sandbox2D::OnMouseMovedEvent(Ganymede::MouseMovedEvent& event) {
    GNM_PROFILE_FUNCTION();
    
    // m_Camera.SetPosition({ m_CameraPosition + mousePos, 0.0f});

    return false;
}

bool Sandbox2D::OnKeyEvent(Ganymede::KeyEvent& event) {
    GNM_PROFILE_FUNCTION();
    
    return false;
}



