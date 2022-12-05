#include "gnmpch.h"
#include "Application.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer/Renderer.h"

namespace Ganymede {

    Application* Application::s_Instance = nullptr;
    
    Application::Application() {
        GNM_CORE_ASSERT(s_Instance == nullptr, "Application instance already exists")
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(GNM_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // TRIANGLE
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float4, "a_Color"},
        };
        float vertices[3 * 7] = {
            -0.5f,  -0.5f,  0.0f,       1.0f,   0.0f,   1.0f,   1.0f,
            0.5f,   -0.5f,  0.0f,       0.0f,   1.0f,   1.0f,   1.0f,
            0.0f,   0.5f,   0.0f,       1.0f,   1.0f,   0.0f,   1.0f,
        };
        uint32_t indices[3 * 1] = {
            0, 1, 2
        };

        m_TriangleVertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());

        std::shared_ptr<VertexBuffer> triangleVertBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
        triangleVertBuffer->SetLayout(layout);
        std::shared_ptr<IndexBuffer> triangleIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, (uint32_t)std::size(indices)));
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

        m_SquareVertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());

        std::shared_ptr<VertexBuffer> squareVertBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVertBuffer->SetLayout(layout); // using same layout, same shader as triangle
        std::shared_ptr<IndexBuffer> squareIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squareIndices, (uint32_t)std::size(squareIndices)));
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
        
        m_Shader = std::shared_ptr<Shader>(Shader::Create(vertexSrc, fragmentSrc));
    }


    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }


    void Application::PushOverlay(Layer *overlay) {
        m_LayerStack.PushOverlay(overlay);
    }


    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GNM_BIND_EVENT_FN(Application::OnWindowClose));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if(e.Handled) {
                break;
            }
        }
    }


    void Application::Run() {
        while (m_Running) {

            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();
            
            Renderer::BeginScene();

            // Render square and triangle with the same shader
            m_Shader->Bind();
            Renderer::Submit(m_SquareVertexArray);
            Renderer::Submit(m_TriangleVertexArray);

            Renderer::EndScene();
            // Renderer::Flush();
            

            
            for(Layer* layer : m_LayerStack) {
                layer->OnUpdate();    
            }

            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            
            m_Window->OnUpdate();
        }
    }


    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }



}
