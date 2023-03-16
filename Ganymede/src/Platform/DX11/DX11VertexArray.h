#pragma once
#include "Ganymede/Renderer/VertexArray.h"

namespace Ganymede {
    class DX11VertexArray : public VertexArray{
    public:
        DX11VertexArray();
        virtual ~DX11VertexArray() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;
        virtual const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() const override { return m_VertexBuffers; }
        virtual const Ref<IndexBuffer> & GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}
