
#include <PlatformWindow.h>

#include "App.h"
#include <PlatformGLContext.h>

#include <windows.h>

#include "Render/RenderManager.h"
#include "Render/RendererType.h"

Window* currentEventWindow = nullptr;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
            App::getInstance()->addWindow(currentEventWindow);
            currentEventWindow->retain();
            printf("create!");
            fflush(stdout);
            break;

        case WM_QUIT:
            printf("quit!");
            fflush(stdout);
            break;

        case WM_CLOSE:
            printf("close!");
            fflush(stdout);
            break;

        case WM_DESTROY:
            App::getInstance()->removeWindow(currentEventWindow);
            currentEventWindow->release();

            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

WinWindow::WinWindow()
{
    SetProcessDPIAware();

    auto hInstance = GetModuleHandle(nullptr);

    LPCWSTR className = L"GameWindow";

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = className;
    RegisterClassEx(&wc);

    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU;

    currentEventWindow = this;

    RECT rect = {0, 0, 800, 800};
    AdjustWindowRect(&rect, dwStyle, false);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    auto title = L"Judy Window";
    hWnd = CreateWindowEx(NULL, className, title, dwStyle, x, y, width, height, nullptr, nullptr, hInstance, nullptr);
    currentEventWindow = nullptr;

    renderTarget = new WinRenderTarget(hInstance, hWnd);
    renderer = RenderManager::getInstance()->getRenderer(RendererType::DX);
}

WinWindow::~WinWindow()
{
}

#include <DXRenderer.h>

void WinWindow::switchRenderType()
{
    static int type = 0;
    type++;
    type = type % (int)RendererType::Count;

    renderer = RenderManager::getInstance()->getRenderer(static_cast<RendererType>(type));
}

void WinWindow::processEvents()
{
    MSG msg;
    currentEventWindow = this;
    while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    currentEventWindow = nullptr;

    while (PeekMessage(&msg, (HWND)-1, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
