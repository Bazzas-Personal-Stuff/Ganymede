﻿#pragma once
#include "GraphicsContext.h"
#include "RendererAPI.h"

namespace Ganymede {
    class RenderCommand {
    public:
        static void Init() {
            s_RendererAPI->Init();
        }

        static void SwapBuffers() {
            s_RendererAPI->SwapBuffers();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(x, y, width, height);
        }
        
        static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear() {
            s_RendererAPI->Clear();
        }
        
        static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
    
}
