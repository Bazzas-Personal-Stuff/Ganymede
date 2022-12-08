﻿#pragma once
#include "glm/glm.hpp"

namespace Ganymede {
    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        void RecalculateViewMatrix();

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) {
            m_Position = position;
            RecalculateViewMatrix();
        }

        float GetRotation() { return m_Rotation; }
        void SetRotation(float rotation) {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }        
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }        
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }        
    private:
        glm::mat4 m_ProjectionMatrix {1.0f};
        glm::mat4 m_ViewMatrix {1.0f};
        glm::mat4 m_ViewProjectionMatrix {1.0f};
        
        glm::vec3 m_Position {0.0f};
        float m_Rotation = 0.0f;
    };
    
}
