﻿#include "gnmpch.h"
#include "Renderer.h"

#include "Renderer2D.h"
#include "Shader.h"

namespace Ganymede {
    Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<SceneData>();

    void Renderer::Init() {
        GNM_PROFILE_FUNCTION();
        RenderCommand::Init();
        // Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
