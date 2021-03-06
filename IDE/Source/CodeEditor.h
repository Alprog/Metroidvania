
#pragma once

#include "Document.h"
#include "SciLexer.h"
#include <QTimer>
#include "string"
#include "../qt/ScintillaEdit.h"

class CodeEditor : public Scintilla::ScintillaEdit
{
    Q_OBJECT

public:
    enum class HighlightType
    {
        None,
        Lua,
        HLSL
    };

    CodeEditor(QWidget* parent = 0);
    void setText(std::string text);
    void setSource(std::string source);
    void setHighlightType(HighlightType type);

    void pullBreakpoints();
    void pushBreakpoints();

private slots:
    void onMarginClicked(int position, int modifiers, int margin);
    void onLinesAdded(int arg);

    void tick();
    void onDwellStart(int x, int y);
    void onDwellEnd(int x, int y);

public slots:
    void updateActiveLine();

private:
    void setLuaLexer();
    void setHlslLexer();

    std::string source;
    QTimer timer;
    int mouseTime;
    QPoint mousePoint;
};
