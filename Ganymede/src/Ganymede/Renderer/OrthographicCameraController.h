#pragma once
#include "Ganymede/Events/ApplicationEvent.h"
#include "Ganymede/Events/Event.h"
#include "Ganymede/Events/MouseEvent.h"
#include "Ganymede/Renderer/OrthographicCamera.h"

namespace Ganymede {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void OnUpdate();
        void OnEvent(Event& e);

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_OrthographicScale = 1.0f;
        OrthographicCamera m_Camera;

        glm::vec3 m_CameraPosition = {0, 0, 0};
        float m_CameraSpeed = 1.0f;
        float m_ZoomSpeed = 0.5f;
    };
}
