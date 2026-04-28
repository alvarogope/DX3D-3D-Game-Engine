#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc)
{
    RenderSystemDesc rsDesc;
    rsDesc.window_handle = desc.window_handle;
    rsDesc.width         = desc.width;
    rsDesc.height        = desc.height;

    m_renderSystem = std::make_unique<RenderSystem>(rsDesc);
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

void dx3d::GraphicsEngine::present(bool vsync)
{
    m_renderSystem->present(vsync);
}

void dx3d::GraphicsEngine::clear(float r, float g, float b)
{
    m_renderSystem->clear(r, g, b);
}