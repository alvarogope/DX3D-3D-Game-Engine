#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d
{
    struct GraphicsEngineDesc
    {
        void* window_handle = nullptr;
        unsigned int width  = 0;
        unsigned int height = 0;
    };

    class GraphicsEngine final : public Base
    {
    public:
        explicit GraphicsEngine(const GraphicsEngineDesc& desc);
        virtual ~GraphicsEngine() override;
		void present(bool vsync);
        void clear(float r, float g, float b);
    private:
        std::unique_ptr<RenderSystem> m_renderSystem{};
    };
}