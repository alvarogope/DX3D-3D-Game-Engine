#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>

namespace dx3d
{
    struct RenderSystemDesc
    {
        void* window_handle = nullptr;
        unsigned int width  = 0;
        unsigned int height = 0;
    };

    class RenderSystem final : public Base
    {
    public:
        explicit RenderSystem(const RenderSystemDesc& desc);
        virtual ~RenderSystem() override;
        void present(bool vsync);
        void clear(float r, float g, float b);
    private:
        Microsoft::WRL::ComPtr<ID3D11Device>        m_d3dDevice{};
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>  m_d3dContext{};
        Microsoft::WRL::ComPtr<IDXGISwapChain>       m_swapChain{};
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView{};
    };
}