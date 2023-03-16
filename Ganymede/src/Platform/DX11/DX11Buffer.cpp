#include "gnmpch.h"
#include "DX11Buffer.h"

namespace Ganymede {

    // Vertex buffer ///////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    DX11VertexBuffer::DX11VertexBuffer(float *vertices, uint32_t size) {
        GNM_PROFILE_FUNCTION();
    }

    DX11VertexBuffer::~DX11VertexBuffer() {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexBuffer::Bind() const {
        GNM_PROFILE_FUNCTION();
    }

    void DX11VertexBuffer::Unbind() const {
        GNM_PROFILE_FUNCTION();
    }


    void DX11VertexBuffer::SetLayout(const BufferLayout &layout) {
        GNM_PROFILE_FUNCTION();
    }


    // Index buffer ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    DX11IndexBuffer::DX11IndexBuffer() {
        GNM_PROFILE_FUNCTION();
    }

    DX11IndexBuffer::~DX11IndexBuffer() {
        GNM_PROFILE_FUNCTION();
    }

    void DX11IndexBuffer::Bind() const {
        GNM_PROFILE_FUNCTION();
    }

    void DX11IndexBuffer::Unbind() const {
        GNM_PROFILE_FUNCTION();
    }
}
