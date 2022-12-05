#include <Ganymede.h>

#include "Ganymede/Renderer/RenderCommand.h"
#include "Ganymede/Renderer/Renderer.h"
#include "Ganymede/Renderer/Shader.h"

class ExampleLayer : public Ganymede::Layer {
public:
    ExampleLayer() : Layer("Example") {
        // TRIANGLE
        Ganymede::BufferLayout layout = {
            { Ganymede::ShaderDataType::Float3, "a_Position"},
            { Ganymede::ShaderDataType::Float4, "a_Color"},
        };
        float vertices[3 * 7] = {
            -0.5f,  -0.5f,  0.0f,       1.0f,   0.0f,   1.0f,   1.0f,
            0.5f,   -0.5f,  0.0f,       0.0f,   1.0f,   1.0f,   1.0f,
            0.0f,   0.5f,   0.0f,       1.0f,   1.0f,   0.0f,   1.0f,
        };
        uint32_t indices[3 * 1] = {
            0, 1, 2
        };

        m_TriangleVertexArray = std::shared_ptr<Ganymede::VertexArray>(Ganymede::VertexArray::Create());

        std::shared_ptr<Ganymede::VertexBuffer> triangleVertBuffer = std::shared_ptr<Ganymede::VertexBuffer>(Ganymede::VertexBuffer::Create(vertices, sizeof(vertices)));
        triangleVertBuffer->SetLayout(layout);
        std::shared_ptr<Ganymede::IndexBuffer> triangleIndexBuffer = std::shared_ptr<Ganymede::IndexBuffer>(Ganymede::IndexBuffer::Create(indices, (uint32_t)std::size(indices)));
        m_TriangleVertexArray->AddVertexBuffer(triangleVertBuffer);
        m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

        // SQUARE
        float squareVertices[4*7] ={
            -0.5f,  -0.5f,  0.0f,       1.0f,   0.0f,   1.0f,   1.0f, 
             0.5f,  -0.5f,  0.0f,       0.0f,   1.0f,   1.0f,   1.0f, 
             0.5f,   0.5f,  0.0f,       1.0f,   1.0f,   0.0f,   1.0f, 
            -0.5f,   0.5f,  0.0f,       1.0f,   1.0f,   1.0f,   1.0f, 
        };
        uint32_t squareIndices[3 * 2] = {
            0, 1, 2,
            2, 3, 0,
        };

        m_SquareVertexArray = std::shared_ptr<Ganymede::VertexArray>(Ganymede::VertexArray::Create());

        std::shared_ptr<Ganymede::VertexBuffer> squareVertBuffer = std::shared_ptr<Ganymede::VertexBuffer>(Ganymede::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVertBuffer->SetLayout(layout); // using same layout, same shader as triangle
        std::shared_ptr<Ganymede::IndexBuffer> squareIndexBuffer = std::shared_ptr<Ganymede::IndexBuffer>(Ganymede::IndexBuffer::Create(squareIndices, (uint32_t)std::size(squareIndices)));
        m_SquareVertexArray->AddVertexBuffer(squareVertBuffer);
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
        
        std::string vertexSrc = R"(
        #version 330 core

        layout(location=0) in vec3 a_Position;
        layout(location=1) in vec4 a_Color;
        out vec3 v_Position;
        out vec4 v_Color;
        
        void main(){
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
        )";

        std::string fragmentSrc = R"(
        #version 330 core

        
        layout(location=0) out vec4 o_Color;
        in vec3 v_Position;
        in vec4 v_Color;
        
        void main(){
            o_Color = v_Color;
            
        }
        )";
        
        m_Shader = std::shared_ptr<Ganymede::Shader>(Ganymede::Shader::Create(vertexSrc, fragmentSrc));
    }

    virtual void OnUpdate() override {
        Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Ganymede::RenderCommand::Clear();

        Ganymede::Renderer::BeginScene();

        // Render square and triangle with the same shader
        m_Shader->Bind();
        Ganymede::Renderer::Submit(m_SquareVertexArray);
        Ganymede::Renderer::Submit(m_TriangleVertexArray);

        Ganymede::Renderer::EndScene();
        // Renderer::Flush();
        
        if(Ganymede::Input::IsKeyPressed(GNM_KEY_SPACE)) {
            GNM_LOG("Space has been pressed!");
        }
    }

    // virtual void OnImGuiRender() override {
    //     ImGui::Begin("Test");
    //     ImGui::Text("Hello World");
    //     ImGui::End();
    // }
    
    virtual void OnEvent(Ganymede::Event& event) override {
    }

    std::shared_ptr<Ganymede::Shader> m_Shader;
    std::shared_ptr<Ganymede::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Ganymede::VertexArray> m_SquareVertexArray;
    
};


class Sandbox : public Ganymede::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox(){}
};

Ganymede::Application* Ganymede::CreateApplication() {
    return new Sandbox();
}