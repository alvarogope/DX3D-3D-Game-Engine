#include <DX3D/Window/Window.h>
#include <Windows.h>

namespace dx3d
{
    static bool s_is_running = false;

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
        case WM_CLOSE:
            s_is_running = false;
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
        }
        return 0;
    }

    Window::Window()
    {
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = L"DX3DWindow";
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        RegisterClassEx(&wc);

        m_handle = CreateWindowEx(
            0, L"DX3DWindow", L"DX3D Engine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            1280, 720,
            nullptr, nullptr,
            GetModuleHandle(nullptr), nullptr
        );

        ShowWindow((HWND)m_handle, SW_SHOW);
        s_is_running = true;
    }

    Window::~Window()
    {
        if (m_handle)
            DestroyWindow((HWND)m_handle);
    }

    bool Window::broadcast()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return s_is_running;
    }
}