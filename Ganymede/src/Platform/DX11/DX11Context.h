#pragma once
#include "Ganymede/Renderer/GraphicsContext.h"

#include <d3d11_4.h>
#include <wrl.h>

#include <utility>

struct GLFWwindow;
enum D3D_FEATURE_LEVEL;

namespace Ganymede {
    class DX11Context : public GraphicsContext {
    public:
        DX11Context(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;

        Microsoft::WRL::ComPtr<ID3D11Device1> GetDevice() { return m_DX11Device; }
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1> GetDeviceContext() { return m_DX11DeviceContext; }
        Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() { return m_SwapChain; }

    private:
        GLFWwindow* m_WindowHandle;
        HWND m_HWnd;
        D3D_FEATURE_LEVEL m_FeatureLevel;
        Microsoft::WRL::ComPtr<ID3D11Device1> m_DX11Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_DX11DeviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;

    };
}
