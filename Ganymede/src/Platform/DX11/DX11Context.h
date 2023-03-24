#pragma once
#include "Ganymede/Renderer/GraphicsContext.h"
#include "glm/vec4.hpp"
#include "glm/detail/func_packing_simd.inl"

#include <d3d11_4.h>
#include <wrl.h>


struct GLFWwindow;

namespace Ganymede {
    class DX11Context : public GraphicsContext {
    public:
        DX11Context(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void Bind() override { s_CurrentContext = this; }
        virtual void SwapBuffers() override;
        
        static DX11Context* GetCurrent() { return s_CurrentContext; }
        Microsoft::WRL::ComPtr<ID3D11Device1> GetDevice() { return m_DX11Device; }
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1> GetDeviceContext() { return m_DX11DeviceContext; }
        Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() { return m_SwapChain; }
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetBackBuffer() { return m_BackBuffer; }

        const glm::vec4 GetClearColor() const { return m_ClearColor; }
        void SetClearColor(const glm::vec4& color) { m_ClearColor = color; }

    private:
        GLFWwindow* m_WindowHandle;
        HWND m_HWnd;
        D3D_FEATURE_LEVEL m_FeatureLevel;

        Microsoft::WRL::ComPtr<ID3D11Device1> m_DX11Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_DX11DeviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_BackBuffer;

        glm::vec4 m_ClearColor;

        static DX11Context* s_CurrentContext;
    };
}
