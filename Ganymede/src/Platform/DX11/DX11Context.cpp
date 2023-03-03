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
        HWND hwnd = glfwGetWin32Window(m_WindowHandle);
        GNM_CORE_ASSERT(hwnd, "Failed to acquire HWND");

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
        // Ref<ID3D11Device> device;
        // Ref<ID3D11DeviceContext> context;

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

        device.As(&m_dx11Device);
        context.As(&m_dx11DeviceContext);

        IDXGIDevice* pDXGIDevice;
        result = device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
        if(SUCCEEDED(result)) {
            IDXGIAdapter* pAdapter;
            result = pDXGIDevice->GetAdapter(&pAdapter);
            if(SUCCEEDED(result)) {
                DXGI_ADAPTER_DESC adapterDesc;
                result = pAdapter->GetDesc(&adapterDesc);
                if(SUCCEEDED(result)) {
                    GNM_CORE_INFO("DirectX11 Info:");
                    GNM_CORE_INFO("  Description: {0}", reinterpret_cast<const char*>(adapterDesc.Description));
                    GNM_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(adapterDesc.VendorId));
                }
                pAdapter->Release();
            }
            pDXGIDevice->Release();
        }
        
        GNM_CORE_INFO("DirectX11 Info:");
        // GNM_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>());
        // GNM_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>());
        // GNM_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>());
    }

    void DX11Context::SwapBuffers() {
    }
}
