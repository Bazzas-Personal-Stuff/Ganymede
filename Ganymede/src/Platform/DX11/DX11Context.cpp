#include "gnmpch.h"
#include "DX11Context.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "Ganymede/Core/Application.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include <d3d11.h>
#include <wrl.h>

namespace Ganymede {
    DX11Context* DX11Context::s_CurrentContext = nullptr;

    DX11Context::DX11Context(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle),
    m_ClearColor(0.0f, 0.0f, 0.0f, 1.0f){
        GNM_CORE_ASSERT(windowHandle, "Window handle is null")
    }

    void DX11Context::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        m_HWnd = glfwGetWin32Window(m_WindowHandle);
        GNM_CORE_ASSERT(m_HWnd, "Failed to acquire HWND");

        UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

        #ifdef GNM_DEBUG
        deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        D3D_FEATURE_LEVEL levels[] = {
                D3D_FEATURE_LEVEL_9_1,
                D3D_FEATURE_LEVEL_9_2,
                D3D_FEATURE_LEVEL_9_3,
                D3D_FEATURE_LEVEL_10_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_11_1,
        };

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = m_HWnd;
        // swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.Windowed = TRUE;

        Microsoft::WRL::ComPtr<ID3D11Device> device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
        
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            deviceFlags,
            levels,
            ARRAYSIZE(levels),
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain,
            &device,
            &m_FeatureLevel,
            &context
        );
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to create DX11 device")

        // cast to dx11.1 versions
        device.As(&m_DX11Device);
        context.As(&m_DX11DeviceContext);
        swapChain.As(&m_SwapChain);

        Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
        result = device.As(&dxgiDevice);
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to query DXGI device")
        
        IDXGIAdapter* adapter;
        result = dxgiDevice->GetAdapter(&adapter);
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to get DXGI adapter")

        DXGI_ADAPTER_DESC adapterDesc;
        result = adapter->GetDesc(&adapterDesc);
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to get DXGI adapter description")

        char descCStr[256];
        sprintf(descCStr, "%ws", adapterDesc.Description);
        
        GNM_CORE_INFO("DirectX11 Info:");
        GNM_CORE_INFO("  GPU: {0}", descCStr);
        GNM_CORE_INFO("  Vendor ID: 0x{0:X}", adapterDesc.VendorId);
        GNM_CORE_INFO("  Device ID: 0x{0:X}", adapterDesc.DeviceId);
        GNM_CORE_INFO("  RAM: {0}", adapterDesc.DedicatedSystemMemory);
        GNM_CORE_INFO("  VRAM: {0:.2f} GB", adapterDesc.DedicatedVideoMemory / 1073741824.0f);

        Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
        adapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

        // Create render target
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBufferSurface;
        result = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBufferSurface);
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to get SwapChain backbuffer");
        
        result = m_DX11Device->CreateRenderTargetView(backBufferSurface.Get(), nullptr, &m_BackBuffer);
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to create render target view");

        // m_DX11DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, nullptr);

        // Set viewport
        int tempWidth, tempHeight;
        glfwGetWindowSize(m_WindowHandle, &tempWidth, &tempHeight);

        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = (FLOAT)tempWidth;
        viewport.Height = (FLOAT)tempHeight;        

        m_DX11DeviceContext->RSSetViewports(1, &viewport);
    }

    void DX11Context::SwapBuffers() {
        HRESULT result = m_SwapChain->Present(0, 0);
        GNM_CORE_ASSERT(SUCCEEDED(result), "SwapChain presentation failed");
    }
}
