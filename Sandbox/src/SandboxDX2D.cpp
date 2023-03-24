#include "SandboxDX2D.h"

#include "Ganymede/Renderer/RenderCommand.h"

SandboxDX2D::SandboxDX2D() : Layer("SandboxDX2D"),
                             m_CameraController(16.0f/9.0f){
    
}

void SandboxDX2D::OnAttach() {
    GNM_PROFILE_FUNCTION();
    Layer::OnAttach();
}

void SandboxDX2D::OnDetach() {
    GNM_PROFILE_FUNCTION();
    Layer::OnDetach();
}

void SandboxDX2D::OnUpdate() {
    GNM_PROFILE_FUNCTION();
    Layer::OnUpdate();

    m_CameraController.OnUpdate();

    {
        GNM_PROFILE_SCOPE("Renderer Prep");
        Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Ganymede::RenderCommand::Clear();
    }
}

void SandboxDX2D::OnImGuiRender() {
    GNM_PROFILE_FUNCTION();
    Layer::OnImGuiRender();
}

void SandboxDX2D::OnEvent(Ganymede::Event &event) {
    GNM_PROFILE_FUNCTION();
    Layer::OnEvent(event);
}
