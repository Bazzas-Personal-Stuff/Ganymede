#include "gnmpch.h"
#include "DX11VertexArray.h"

namespace Ganymede {
    DX11VertexArray::DX11VertexArray() {
        GNM_PROFILE_FUNCTION();
        
    }

    DX11VertexArray::~DX11VertexArray() {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexArray::Bind() const {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexArray::Unbind() const {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        GNM_PROFILE_FUNCTION();
    }
}
