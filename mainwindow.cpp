#include <QtGui>
#include "mainwindow.h"
#include "loggingwidget.h"
#include "scenetreewidget.h"
#include "glview.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    m_logging=new LoggingWidget;
    setupDock(m_logging,
            tr("Log"),
            Qt::BottomDockWidgetArea,
            Qt::BottomDockWidgetArea
            );

    setupDock(new SceneTreeWidget,
            tr("Scene"), 
            Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea,
            Qt::LeftDockWidgetArea
            );

    auto glv=new GLView();
    setCentralWidget(glv);

    // file menu
    auto file=menuBar()->addMenu(tr("&File"));

    auto open=new QAction("&Open", this);
    file->addAction(open);

    auto quit=new QAction("&Quit", this);
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QObject::connect(open, SIGNAL(triggered()), 
            this, SLOT(onOpen()));

    QObject::connect(this, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 
}

void MainWindow::setupDock(QWidget *w, const QString &dockTitle, 
        int allow, Qt::DockWidgetArea add)
{
    auto dock = new QDockWidget(dockTitle, this);
    dock->setAllowedAreas(static_cast<Qt::DockWidgetArea>(allow));
    dock->setWidget(w);
    addDockWidget(add, dock);
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(
            this, tr("Open File"),
            ".",
            tr("ply file (*.ply)"));
    if(path.isEmpty()){
        return;
    }
    logging(QString("open %1").arg(path));
}

