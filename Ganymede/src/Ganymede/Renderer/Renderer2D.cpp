#include "gnmpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "glm/gtx/transform.hpp"

namespace Ganymede {
    struct Renderer2DData {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> Shader;
        Ref<Texture2D> WhiteTex;
    };

    static Renderer2DData* s_Data;

    void Renderer2D::Init() {
        GNM_PROFILE_FUNCTION();
        s_Data = new Renderer2DData();
        
        // SQUARE
        s_Data->QuadVertexArray = VertexArray::Create();
        float squareVertices[4 * 5] ={
            -0.5f,  -0.5f,  0.0f,       0.0f,   0.0f,
             0.5f,  -0.5f,  0.0f,       1.0f,   0.0f,
             0.5f,   0.5f,  0.0f,       1.0f,   1.0f,
            -0.5f,   0.5f,  0.0f,       0.0f,   1.0f,
        };
        
        auto squareVertBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVertBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float2, "a_TexCoord"},
        }); 
        s_Data->QuadVertexArray->AddVertexBuffer(squareVertBuffer);

        uint32_t squareIndices[2 * 3] = {
            0, 1, 2,
            2, 3, 0,
        };
        auto squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

        s_Data->Shader = Shader::Create("assets/shaders/Sprite.glsl");
        s_Data->Shader->Bind();
        s_Data->Shader->SetInt("u_Texture", 0);

        s_Data->WhiteTex = Texture2D::Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    void Renderer2D::Shutdown() {
        GNM_PROFILE_FUNCTION();
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        GNM_PROFILE_FUNCTION();
        s_Data->Shader->Bind();
        s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        GNM_PROFILE_FUNCTION();
    }


    // Primitives
    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size) {
        DrawQuad(position, 0.0f, size, {1.0f, 1.0f, 1.0f, 1.0f}, s_Data->WhiteTex);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad(position, 0.0f, size, color, s_Data->WhiteTex);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture) {
        DrawQuad(position, 0.0f, size, {1.0f, 1.0f, 1.0f, 1.0f}, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position,
        const glm::vec2 &size,
        const glm::vec4 &color,
        const Ref<Texture2D> &texture) {
        
        DrawQuad(position, 0.0f, size, color, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position,
        const float rotation,
        const glm::vec2 &size,
        const glm::vec4 &color) {

        DrawQuad(position, rotation, size, color, s_Data->WhiteTex);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position,
        const float rotation,
        const glm::vec2 &size,
        const Ref<Texture2D> &texture) {
        DrawQuad(position, rotation, size, {1.0f, 1.0f, 1.0f, 1.0f}, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const float rotation, const glm::vec2 &size, const glm::vec4 &color, const Ref<Texture2D> &texture) {
        GNM_PROFILE_FUNCTION();
        // Calculate TRS transform matrix
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * 
            glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        s_Data->Shader->SetMat4("u_Transform", transform);
        s_Data->Shader->SetFloat4("u_Color", color);
        
        s_Data->QuadVertexArray->Bind();
        texture->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}
