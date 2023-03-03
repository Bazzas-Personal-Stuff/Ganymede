#include "gnmpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ganymede {
    struct Renderer2DData {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> Shader;
        
    };

    static Renderer2DData* s_Data;

    void Renderer2D::Init() {
        s_Data = new Renderer2DData();
        
        // SQUARE
        s_Data->QuadVertexArray = VertexArray::Create();
        float squareVertices[4 * 3] ={
            -0.5f,  -0.5f,  0.0f,       
             0.5f,  -0.5f,  0.0f,       
             0.5f,   0.5f,  0.0f,       
            -0.5f,   0.5f,  0.0f,       
        };
        
        auto squareVertBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVertBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
        }); 
        s_Data->QuadVertexArray->AddVertexBuffer(squareVertBuffer);

        uint32_t squareIndices[2 * 3] = {
            0, 1, 2,
            2, 3, 0,
        };
        auto squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

        s_Data->Shader = Shader::Create("assets/shaders/FlatColor.glsl");
    }

    void Renderer2D::Shutdown() {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene() {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->UploadUniformFloat4("u_Color", color);
        
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        // Renderer::Submit(s_Data->Shader, s_Data->QuadVertexArray);
    }
}
