
#pragma once

#include "Window.h"
#include "Render/RenderTarget.h"

#define Window XWindow
#include <X11/X.h>
#include <X11/Xlib.h>
#undef Window

class LinuxWindow : public Window
{
public:
    LinuxWindow();

    virtual void processEvents();
    virtual void switchRenderType();

    Display* display;
    XWindow window;
};

using PlatformWindow = LinuxWindow;
