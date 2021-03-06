
include(../Default.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp \
    Source/Parser/Statement.cpp \
    Source/Parser/Snippet.cpp \
    Source/Parser/Tokens/AtomToken.cpp \
    Source/Parser/Tokens/Token.cpp \
    Source/Parser/Tokens/TokenGroup.cpp \
    Source/Info/ArgumentInfo.cpp \
    Source/Info/MemberInfo.cpp \
    Source/Info/TypeInfo.cpp \
    Source/Info/MethodInfo.cpp \
    Source/Info/ClassInfo.cpp \
    Source/Info/InheritanceInfo.cpp \
    Source/Info/FieldInfo.cpp \
    Source/Info/NamespaceInfo.cpp \
    Source/Info/AttributeInfo.cpp \
    Source/Generator/CodeGenerator.cpp \
    Source/Parser/CodeParser.cpp \
    Source/Info/Specifier.cpp \
    Source/Info/PropertyInfo.cpp

CONFIG += qt

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}

HEADERS += \
    Source/Parser/Statement.h \
    Source/Parser/Snippet.h \
    Source/Parser/RegexConstants.h \
    Source/Parser/Tokens/AtomToken.h \
    Source/Parser/Tokens/Token.h \
    Source/Parser/Tokens/TokenGroup.h \
    Source/Info/AccessModifier.h \
    Source/Info/ArgumentInfo.h \
    Source/Info/MemberInfo.h \
    Source/Info/TypeInfo.h \
    Source/Info/MethodInfo.h \
    Source/Info/ClassInfo.h \
    Source/Info/InheritanceInfo.h \
    Source/Info/FieldInfo.h \
    Source/Info/NamespaceInfo.h \
    Source/Info/AttributeInfo.h \
    Source/Info/ClassType.h \
    Source/Generator/CodeGenerator.h \
    Source/Parser/CodeParser.h \
    Source/Info/Specifier.h \
    Source/Info/PropertyInfo.h
