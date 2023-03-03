#pragma once
#include "Ganymede/Renderer/GraphicsContext.h"

#include <d3d11.h>
#include <wrl.h>

struct GLFWwindow;
enum D3D_FEATURE_LEVEL;

namespace Ganymede {
    class DX11Context : public GraphicsContext {
    public:
        DX11Context(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
        D3D_FEATURE_LEVEL m_FeatureLevel;
        Microsoft::WRL::ComPtr<ID3D11Device> m_dx11Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_dx11DeviceContext;
    };
}
