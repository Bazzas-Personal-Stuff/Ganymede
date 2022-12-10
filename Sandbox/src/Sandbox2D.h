﻿#pragma once
#include <Ganymede.h>

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
    Ganymede::OrthographicCamera m_Camera;
    std::shared_ptr<Ganymede::Shader> m_MultiColorShader;
    std::shared_ptr<Ganymede::Shader> m_FlatColorShader;
    std::shared_ptr<Ganymede::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Ganymede::VertexArray> m_SquareVertexArray;

    glm::vec2 m_CameraPosition {0.0f};
    glm::vec3 m_SquarePosition {0.0f};
    glm::vec4 m_FlatColor {0.8f, 0.2f, 0.2f, 1.0f};
    float m_CameraSpeed = 1.0f;
    float m_SquareSpeed = 1.0f;
    
};
