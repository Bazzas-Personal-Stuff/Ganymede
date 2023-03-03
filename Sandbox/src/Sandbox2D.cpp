#include "Sandbox2D.h"

#include "Ganymede/Events/KeyEvent.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
    m_CameraController(16.0f/9.0f){

    // TRIANGLE
    // float vertices[3 * 7] = {
    //     -0.5f,  -0.5f,  0.0f,       1.0f,   0.0f,   1.0f,   1.0f,
    //     0.5f,   -0.5f,  0.0f,       0.0f,   1.0f,   1.0f,   1.0f,
    //     0.0f,   0.5f,   0.0f,       1.0f,   1.0f,   0.0f,   1.0f,
    // };
    // uint32_t indices[3 * 1] = {
    //     0, 1, 2
    // };
    //
    // m_TriangleVertexArray = Ganymede::Ref(Ganymede::VertexArray::Create());
    //
    // auto triangleVertBuffer = Ganymede::Ref(Ganymede::VertexBuffer::Create(vertices, sizeof(vertices)));
    // triangleVertBuffer->SetLayout({
    //     { Ganymede::ShaderDataType::Float3, "a_Position"},
    //     { Ganymede::ShaderDataType::Float4, "a_Color"},
    // });
    // auto triangleIndexBuffer = Ganymede::Ref(Ganymede::IndexBuffer::Create(indices, (uint32_t)std::size(indices)));
    // m_TriangleVertexArray->AddVertexBuffer(triangleVertBuffer);
    // m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);
    //
    // // ============================== Multicolor Shader ===================================
    // auto multiColorShader = m_ShaderLibrary.Load("assets/shaders/MultiColor.glsl");
    //
    // // ============================== Textured Shader =====================================
    //
    // auto spriteShader = m_ShaderLibrary.Load("assets/shaders/Sprite.glsl");
    //
    // m_Texture = Ganymede::Texture2D::Create("assets/textures/dude.png");
}

void Sandbox2D::OnAttach() {
    Layer::OnAttach();
}

void Sandbox2D::OnDetach() {
    Layer::OnDetach();
}

void Sandbox2D::OnUpdate() {
    m_CameraController.OnUpdate();
    
    Ganymede::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Ganymede::RenderCommand::Clear();

    // float deltaTime = Ganymede::Time::Delta();

    // --------- Square movement ---
    // if(Ganymede::Input::GetKey(GNM_KEY_E)) {
    //     m_SquarePosition.x += deltaTime * m_SquareSpeed;
    // }
    // if(Ganymede::Input::GetKey(GNM_KEY_Q)) {
    //     m_SquarePosition.x -= deltaTime * m_SquareSpeed;
    // }

    // mouse
    // glm::mat4 squareTransform = glm::translate(glm::mat4(0.1f), m_SquarePosition);

    // Set flat color based on UI-picked color
    // TODO: Shader::SetFloat4
    // auto spriteShader = m_ShaderLibrary.Get("Sprite");
    // spriteShader->Bind();
    // std::dynamic_pointer_cast<Ganymede::OpenGLShader>(spriteShader)->UploadUniformFloat4("u_Color", m_FlatColor);
    // m_Texture->Bind(0);
    // std::dynamic_pointer_cast<Ganymede::OpenGLShader>(spriteShader)->UploadUniformInt("u_Texture", 0);
    //
    // auto multicolorShader = m_ShaderLibrary.Get("MultiColor");
    
    // -----------------------------

    // --------- RENDER ------------
    // Ganymede::Renderer::BeginScene(m_CameraController.GetCamera());
    //
    // Ganymede::Renderer::Submit(multicolorShader, m_TriangleVertexArray);
    // Ganymede::Renderer::Submit(texturedShader, m_SquareVertexArray, squareTransform);
    //
    // Ganymede::Renderer::EndScene();
    // Renderer::Flush();

    Ganymede::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Ganymede::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_FlatColor);
    Ganymede::Renderer2D::EndScene();

    // -----------------------------
    
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_FlatColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Ganymede::Event& e) {
    // Ganymede::EventDispatcher dispatcher(e);
    m_CameraController.OnEvent(e);        
}

bool Sandbox2D::OnMouseMovedEvent(Ganymede::MouseMovedEvent& event) {
    // m_Camera.SetPosition({ m_CameraPosition + mousePos, 0.0f});

    return false;
}

bool Sandbox2D::OnKeyEvent(Ganymede::KeyEvent& event) {
    return false;
}



