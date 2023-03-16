#pragma once
#include "Ganymede/Renderer/Buffer.h"

namespace Ganymede {
    class DX11VertexBuffer : public VertexBuffer {
    public:
        DX11VertexBuffer(float* vertices, uint32_t size);
        virtual ~DX11VertexBuffer() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const BufferLayout &layout) override;

        virtual const BufferLayout & GetLayout() const override { return m_Layout; }

    private:
        BufferLayout m_Layout;
    };


    class DX11IndexBuffer : public IndexBuffer {
    public:
        DX11IndexBuffer();
        virtual ~DX11IndexBuffer() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }
        
    private:
        uint32_t m_Count;
    };
}
