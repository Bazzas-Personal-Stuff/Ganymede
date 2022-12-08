#pragma once
#include <Ganymede.h>
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

private:
    Ganymede::OrthographicCamera m_Camera;
    std::shared_ptr<Ganymede::Shader> m_Shader;
    std::shared_ptr<Ganymede::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Ganymede::VertexArray> m_SquareVertexArray;
    
};
