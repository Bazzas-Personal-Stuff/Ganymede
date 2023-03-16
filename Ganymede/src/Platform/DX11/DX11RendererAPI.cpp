#include "gnmpch.h"
#include "DX11RendererAPI.h"
#include "DX11Context.h"
#include "Ganymede/Renderer/RenderCommand.h"

namespace Ganymede {
    void DX11RendererAPI::Init() {
        
        // alpha blend
        ID3D11BlendState1* blendState;
        // depth test
    }

    void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        
    }

    void DX11RendererAPI::SetClearColor(const glm::vec4 &color) {
        
    }

    void DX11RendererAPI::Clear() {
    }

    void DX11RendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray) {
    }
}
