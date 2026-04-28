#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>

dx3d::Game::Game()
{
    m_loggerPtr = std::make_unique<Logger>(Logger::LogLevel::Info);
    m_display   = std::make_unique<Window>();

    GraphicsEngineDesc geDesc;
    geDesc.window_handle = m_display->getHandle();
    geDesc.width         = 1280;
    geDesc.height        = 720;

    m_graphicsEngine = std::make_unique<GraphicsEngine>(geDesc);

    m_loggerPtr->log(Logger::LogLevel::Info, "Game initialized.");
}

dx3d::Game::~Game()
{
    m_loggerPtr->log(Logger::LogLevel::Info, "Game closing..");
}

void dx3d::Game::run()
{
    while (m_display->broadcast())
    {
		m_graphicsEngine->present(true);
    }
}