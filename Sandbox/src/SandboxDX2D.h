#pragma once
#include "Ganymede/Core/Layer.h"
#include "Ganymede/Renderer/OrthographicCameraController.h"

class SandboxDX2D : public Ganymede::Layer{
public:
    SandboxDX2D();
    virtual ~SandboxDX2D() override = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Ganymede::Event &event) override;

private:
    Ganymede::OrthographicCameraController m_CameraController;
};
