#include "Sandbox2D.h"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
    m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {

    
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

    uniform mat4 u_ViewProjection;
    
    out vec3 v_Position;
    out vec4 v_Color;
    
    void main(){
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

void Sandbox2D::OnAttach() {
    Layer::OnAttach();
}

void Sandbox2D::OnDetach() {
    Layer::OnDetach();
}

void Sandbox2D::OnUpdate() {
    Layer::OnUpdate();
    Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Ganymede::RenderCommand::Clear();

    // --------- RENDER ------------
    Ganymede::Renderer::BeginScene(m_Camera);

    // Render square and triangle with the same shader
    Ganymede::Renderer::Submit(m_Shader, m_SquareVertexArray);
    Ganymede::Renderer::Submit(m_Shader, m_TriangleVertexArray);

    Ganymede::Renderer::EndScene();
    // Renderer::Flush();
    // -----------------------------
    
}

void Sandbox2D::OnImGuiRender() {
    Layer::OnImGuiRender();
}

void Sandbox2D::OnEvent(Ganymede::Event& event) {
    Ganymede::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Ganymede::MouseMovedEvent>(GNM_BIND_EVENT_FN(Sandbox2D::OnMouseMovedEvent));
}

bool Sandbox2D::OnMouseMovedEvent(Ganymede::MouseMovedEvent& event) {
    float width = (float)Ganymede::Application::Get().GetWindow().GetWidth();
    float height = (float)Ganymede::Application::Get().GetWindow().GetHeight();

    glm::vec2 mousePos {event.GetX(), event.GetY()};
    mousePos -= glm::vec2({width/2.f, height/2.f});
    mousePos *= 1.0f / height;
    mousePos.y *= -1;
    m_Camera.SetPosition({ mousePos, 0.0f});
    m_Camera.SetRotation(mousePos.x * 30.0f);

    return false;
}


