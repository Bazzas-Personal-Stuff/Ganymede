#include "gnmpch.h"
#include "DX11RendererAPI.h"
#include "DX11Context.h"
#include "Ganymede/Renderer/RenderCommand.h"
#include "glm/gtc/type_ptr.hpp"

namespace Ganymede {
    void DX11RendererAPI::Init() {
        
        // alpha blend
        ID3D11BlendState1* blendState;
        // depth test
    }

    void DX11RendererAPI::SwapBuffers() {
        DX11Context::GetCurrent()->SwapBuffers();
    }


    void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        GNM_CORE_LOG("Set Viewport Size");
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = x;
        viewport.TopLeftY = y;
        viewport.Width = width;
        viewport.Height = height;

        DX11Context::GetCurrent()->GetDeviceContext()->RSSetViewports(1, &viewport);
    }

    void DX11RendererAPI::SetClearColor(const glm::vec4 &color) {
        DX11Context::GetCurrent()->SetClearColor(color);
    }

    void DX11RendererAPI::Clear() {
        DX11Context* ctx = DX11Context::GetCurrent();
        glm::vec4 clearColor = ctx->GetClearColor();
        
        ctx->GetDeviceContext()->ClearRenderTargetView(ctx->GetBackBuffer().Get(), glm::value_ptr(clearColor));
    }

    void DX11RendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray) {
    }
}
