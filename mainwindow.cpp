#include <QtGui>
#include "mainwindow.h"
#include "scenetreewidget.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setupDock(new SceneTreeWidget,
            tr("Scene"), 
            Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea,
            Qt::LeftDockWidgetArea
            );
}

void MainWindow::setupDock(QWidget *w, const QString &dockTitle, 
        int allow, Qt::DockWidgetArea add)
{
    auto dock = new QDockWidget(dockTitle, this);
    dock->setAllowedAreas(static_cast<Qt::DockWidgetArea>(allow));
    dock->setWidget(w);
    addDockWidget(add, dock);
}

