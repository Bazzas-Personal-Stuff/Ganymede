#include "gnmpch.h"
#include "DX11Context.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "Ganymede/Core/Application.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include <d3d11.h>
#include <wrl.h>

namespace Ganymede {

    DX11Context::DX11Context(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle){
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

        Microsoft::WRL::ComPtr<ID3D11Device> device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        HRESULT result = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            deviceFlags,
            levels,
            ARRAYSIZE(levels),
            D3D11_SDK_VERSION,
            &device,
            &m_FeatureLevel,
            &context
        );
        GNM_CORE_ASSERT(SUCCEEDED(result), "Failed to create DX11 device")

        // cast to dx11.1 versions
        device.As(&m_DX11Device);
        context.As(&m_DX11DeviceContext);

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
        
        // Create swapchain
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
        // swapChainDesc.Width = m_WindowHandle
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.SampleDesc.Count = 1;
        dxgiFactory->CreateSwapChainForHwnd(
            device.Get(),
            m_HWnd,
            &swapChainDesc,
            nullptr,
            nullptr,
            &m_SwapChain
            );


    }

    void DX11Context::SwapBuffers() {
        m_SwapChain->Present1(1, 0, nullptr);
    }
}
