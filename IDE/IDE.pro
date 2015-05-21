
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

HEADERS += \
    Source/MainWindow.h \
    Source/Document.h \
    Source/TextEditor.h \
    Source/DocumentsPane.h

SOURCES += \
    Source/MainWindow.cpp \
    Source/Main.cpp \
    Source/Document.cpp \
    Source/TextEditor.cpp \
    Source/DocumentsPane.cpp \

INCLUDEPATH += "../3rd-party/scintilla/include"

win {
    LIBS += -L"../3rd-party" -lscintillaedit3
}

linux {
    LIBS += -L"../3rd-party" -lScintillaEdit
}

mac {
    LIBS += -F"../3rd-party" -framework ScintillaEdit
}

RESOURCES = ide.qrc
