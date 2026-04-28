#include <DX3D/Graphics/RenderSystem.h>
#include <stdexcept>

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc)
{
    D3D_FEATURE_LEVEL featureLevel{};
    UINT createDeviceFlags{};

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    auto hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, 0, D3D11_SDK_VERSION,
        m_d3dDevice.GetAddressOf(), &featureLevel, m_d3dContext.GetAddressOf());

    if (FAILED(hr))
        throw std::runtime_error("RenderSystem: Failed to create D3D11 device.");

    // Get the DXGI factory from the device
    Microsoft::WRL::ComPtr<IDXGIDevice>  dxgiDevice;
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
    Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

    m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice);
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &dxgiAdapter);
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory);

    // Swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = desc.width;
    swapChainDesc.BufferDesc.Height = desc.height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = (HWND)desc.window_handle;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    hr = dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.GetAddressOf());

    if (FAILED(hr))
        throw std::runtime_error("RenderSystem: Failed to create swap chain.");
}

dx3d::RenderSystem::~RenderSystem()
{
}

void dx3d::RenderSystem::present(bool vsync)
{
    m_swapChain->Present(vsync ? 1 : 0, 0);
}