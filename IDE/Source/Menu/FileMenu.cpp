
#include "FileMenu.h"
#include <QFileDialog>

#include "../LuaDocument.h"
#include "../HlslDocument.h"
#include "../CrossCompiler/CrossCompiler.h"

FileMenu::FileMenu(MainWindow* window)
    : BaseMenu{"File", window}
{
    QList<QAction*> actions
    {
        createAction("New", "new", SLOT(newFile()), QKeySequence::New),
        createAction("Open", "open", SLOT(openFile()), QKeySequence::Open),
        createAction("Save", "save", SLOT(saveFile()), QKeySequence::Save),
        createAction("Save As", "", SLOT(saveAsFile()), QKeySequence::SaveAs),
        createAction("Compile", "", SLOT(compile()), Qt::Key_F3)
    };
    addActions(actions);
}

void FileMenu::newFile()
{
}

void FileMenu::openFile()
{
    auto filter = tr("Any supported (*.lua *.hlsl *.scene);;Lua (*.lua);;HLSL (*.hlsl);;Scene (*.scene)");
    auto fileName = QFileDialog::getOpenFileName(window, tr("Open File"), "", filter);
    if (!fileName.isEmpty())
    {
        window->documents->open(fileName.toUtf8().constData());
    }
}

void FileMenu::saveFile()
{
    window->documents->saveCurrentDocument();
}

void FileMenu::saveAsFile()
{
}

void FileMenu::compile()
{
    IDocument* document = window->documents->getCurrentDocument();
//    if (document && document->getType() == DocumentType::Text)
//    {
//        auto text = static_cast<TextDocument*>(document)->getText();
//        CrossCompiler::getInstance()->Translate(text);
//    }
}
