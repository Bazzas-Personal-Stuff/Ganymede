#pragma once
#include "Ganymede/Layer.h"
#include "Ganymede/Renderer/OrthographicCamera.h"
#include "Ganymede/Renderer/Shader.h"
#include "Ganymede/Renderer/VertexArray.h"

class Sandbox2D : public Ganymede::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() override = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Ganymede::Event& event) override;
    void OnMouseMovedEvent(int deltaX, int deltaY);

private:
    Ganymede::OrthographicCamera m_Camera;
    std::shared_ptr<Ganymede::Shader> m_Shader;
    std::shared_ptr<Ganymede::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Ganymede::VertexArray> m_SquareVertexArray;
    
};
