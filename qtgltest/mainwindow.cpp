#include <QtGui>
#include <qmenubar.h>
#include <qdockwidget.h>
#include <qfiledialog.h>
#include "mainwindow.h"
#include "loggingwidget.h"
#include "scenetreewidget.h"
#include "glview.h"
#include "scenemodel.h"
#include "scenenodewidget.h"
#include "SceneNode.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_logging(0), m_scene(new SceneModel), m_sceneTreeView(0)
{
    m_logging=new LoggingWidget;
    QObject::connect(this, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 
    QObject::connect(m_scene, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 

    setupDock(m_logging,
            tr("Log"),
            Qt::BottomDockWidgetArea,
            Qt::BottomDockWidgetArea
            );

    auto m_sceneTreeView=new SceneTreeWidget(m_scene);
    setupDock(m_sceneTreeView,
            tr("Scene"), 
            Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea,
            Qt::LeftDockWidgetArea
            );

    QObject::connect(m_sceneTreeView, SIGNAL(doubleClicked(const QModelIndex &)),
            this, SLOT(onSceneItemActivated(const QModelIndex &)));

    auto glv=new GLView(m_scene);
    setCentralWidget(glv);
    QObject::connect(glv, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 
    QObject::connect(m_scene, SIGNAL(repaint()),
            glv, SLOT(update()));

    // file menu
    auto file=menuBar()->addMenu(tr("&File"));

    auto open=new QAction("&Open", this);
    file->addAction(open);

    auto quit=new QAction("&Quit", this);
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QObject::connect(open, SIGNAL(triggered()), 
            this, SLOT(onOpen()));
}

void MainWindow::setupDock(QWidget *w, const QString &dockTitle, 
        int allow, Qt::DockWidgetArea add)
{
    auto dock = new QDockWidget(dockTitle, this);
    dock->setAllowedAreas(static_cast<Qt::DockWidgetArea>(allow));
    dock->setWidget(w);
    addDockWidget(add, dock);

    if(w==m_logging){
        return;
    }
    QObject::connect(w, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(
            this, tr("Open File"),
            ".",
            tr(
                "pmd file (*.pmd)"
                ";;ply file (*.ply)"
                ";;all file (*.*)"
                ));
    if(path.isEmpty()){
        return;
    }

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        logging(QString("fail to open %1").arg(path));
        return;
    }

    m_scene->loadFile(path);
}

void MainWindow::onSceneItemActivated(const QModelIndex &index)
{
    auto node=m_scene->itemForIndex(index);
    if(!node){
        logging("no such node");
        return;
    }

    auto w=new SceneNodeWidget(node);
    setupDock(w, node->name().c_str(),
            Qt::RightDockWidgetArea | Qt::RightDockWidgetArea,
            Qt::RightDockWidgetArea
            );
}

