
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"
    #include "Win/WinProcess.h"
    #include "Win/WinSocket.h"
    #include "Win/WinRenderTarget.h"
    #include <Win/WinInputSystem.h>

    using PlatformApp = WinApp;
    using PlatformWindow = WinWindow;
    using PlatformProcess = WinProcess;
    using PlatformSocket = WinSocket;
    using PlatformRenderTarget = WinRenderTarget;
    using PlatformInputSystem = WinInputSystem;
    using PlatformGLContext = WinGLContext;
#endif

#if defined(LINUX) || defined(MAC)
    #include "Unix/UnixProcess.h"
    #include "Unix/UnixSocket.h"

    using PlatformProcess = UnixProcess;
    using PlatformSocket = UnixSocket;
#endif

#ifdef LINUX
    #include "Render/GL/Linux/LinuxGLContext.h"

    using PlatformGLContext = LinuxGLContext;
#endif

#ifdef MAC
    #include "Mac/MacApp.h"
    #include "Mac/MacWindow.h"

    using PlatformApp = MacApp;
    using PlatformWindow = MacWindow;
#endif


