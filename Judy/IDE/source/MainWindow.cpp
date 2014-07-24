
#include "MainWindow.h"
#include "QAction.h"
#include "QMenuBar.h"
#include "QToolBar.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Judy");

    createActions();
}

QAction* MainWindow::createAction(const char* name, const char* icon, const char* slot, QKeySequence::StandardKey shortcut)
{
    auto action = new QAction(QIcon(icon), tr(name), this);
    action->setShortcuts(shortcut);
    connect(action, SIGNAL(triggered), this, slot);
    return action;
}

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));

    QAction* actions[]
    {
        createAction("&New", ":/images/new.png", SLOT(newFile()), QKeySequence::New),
        createAction("&Open", ":/images/open.png", SLOT(openFile()), QKeySequence::Open),
        createAction("&Save", ":/images/save.png", SLOT(saveFile()), QKeySequence::Save),
        createAction("&SaveAs", NULL, SLOT(saveAsFile()), QKeySequence::SaveAs)
    };

    for (auto action : actions)
    {
        fileMenu->addAction(action);
        fileToolBar->addAction(action);
    }
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::saveAsFile()
{

}
