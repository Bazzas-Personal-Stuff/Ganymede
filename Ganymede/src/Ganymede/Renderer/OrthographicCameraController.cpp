#include "gnmpch.h"
#include "OrthographicCameraController.h"

#include "Ganymede/Core/Input.h"
#include "Ganymede/Core/KeyCodes.h"
#include "Ganymede/Core/Time.h"

namespace Ganymede {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio)
    : m_AspectRatio(aspectRatio),
    m_Camera(-m_AspectRatio * m_OrthographicScale, m_AspectRatio * m_OrthographicScale, -m_OrthographicScale, m_OrthographicScale ) {
        
    }

    void OrthographicCameraController::OnUpdate() {
        // --------- Camera movement ---

        glm::vec3 wishDir {0.0f, 0.0f, 0.0f };
        if(Input::GetKey(GNM_KEY_W)) {
            wishDir.y += 1;
        }
        if(Input::GetKey(GNM_KEY_S)) {
            wishDir.y -= 1;
        }
        if(Input::GetKey(GNM_KEY_D)) {
            wishDir.x += 1;
        }
        if(Input::GetKey(GNM_KEY_A)) {
            wishDir.x -= 1;
        }

        float cameraVel = m_CameraSpeed * m_OrthographicScale * Time::Delta();
        m_CameraPosition += wishDir * cameraVel;
        
        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(GNM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(GNM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
        m_OrthographicScale -= e.GetOffsetY() * m_ZoomSpeed;
        m_OrthographicScale = std::max(m_OrthographicScale, 0.01f);
        m_Camera.SetProjection(-m_AspectRatio * m_OrthographicScale, m_AspectRatio * m_OrthographicScale, -m_OrthographicScale, m_OrthographicScale );
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_OrthographicScale, m_AspectRatio * m_OrthographicScale, -m_OrthographicScale, m_OrthographicScale );
        return false;
    }
}
