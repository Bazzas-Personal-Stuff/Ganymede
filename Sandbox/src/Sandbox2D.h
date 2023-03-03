#pragma once
#include <Ganymede.h>

#include "Ganymede/Renderer/OrthographicCameraController.h"
#include "Ganymede/Events/KeyEvent.h"
#include "Ganymede/Events/MouseEvent.h"

class Sandbox2D : public Ganymede::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() override = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Ganymede::Event& event) override;
    bool OnMouseMovedEvent(Ganymede::MouseMovedEvent& event);
    bool OnKeyEvent(Ganymede::KeyEvent& event);

private:
        
    Ganymede::OrthographicCameraController m_CameraController;
    Ganymede::ShaderLibrary m_ShaderLibrary;
    // Ganymede::Ref<Ganymede::Shader> m_MultiColorShader;
    // Ganymede::Ref<Ganymede::Shader> m_TexturedShader;
    Ganymede::Ref<Ganymede::VertexArray> m_TriangleVertexArray;
    Ganymede::Ref<Ganymede::VertexArray> m_SquareVertexArray;
    Ganymede::Ref<Ganymede::Texture2D> m_Texture;

    glm::vec2 m_CameraPosition {0.0f};
    glm::vec3 m_SquarePosition {1.0f, 0.0f, 0.0f};
    glm::vec4 m_FlatColor {1.0f};
    float m_SquareSpeed = 1.0f;

    // Temp
    // Ganymede::Ref<Ganymede::Shader> m_Shader;
};
