
win {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Win"

    LIBS += -L"..\Engine" -lEngine
    LIBS += -L"..\3rd-Party\zlib" -lzlib
    LIBS += -L"..\3rd-Party\libpng" -llibpng
    PRE_TARGETDEPS += "..\Engine\Engine.lib"
    PRE_TARGETDEPS += "..\3rd-Party\zlib\zlib.lib"
    PRE_TARGETDEPS += "..\3rd-Party\libpng\libpng.lib"


    LIBS += -lUser32 -lGdi32 -ld3d11 -ldxgi -lOpengl32
    LIBS += -ld3dCompiler

    LIBS += -L"..\..\.." -ld3dx11
}

linux {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Linux"
    LIBS += -L"../Engine" -lEngine
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    LIBS += -lX11 -lGL
}

mac {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Mac"
    LIBS += -L"../Engine" -lEngine
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    LIBS += -framework Cocoa -framework OpenGL
}
