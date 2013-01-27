#include <QtGui>
#include "mainwindow.h"
#include "loggingwidget.h"
#include "scenetreewidget.h"
#include "glview.h"
#include "OpenGLScene.h"
#include "IndexedVertexBuffer.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_scene(new OpenGLScene)
{
    m_logging=new LoggingWidget;
    QObject::connect(this, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 

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

    auto glv=new GLView(m_scene);
    setCentralWidget(glv);
    QObject::connect(glv, SIGNAL(logging(const QString &)), 
            m_logging, SLOT(receive(const QString &))); 

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
            tr("ply file (*.ply)"));
    if(path.isEmpty()){
        return;
    }

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        logging(QString("fail to open %1").arg(path));
        return;
    }

    std::vector<char> buffer(file.size());
    if(buffer.empty()){
        logging("empty file");
        return;
    }

    QDataStream in(&file);
    if(in.readRawData(&buffer[0], buffer.size())==-1){
        logging("fail to read file");
        return;
    }

    auto model=IndexedVertexBuffer::CreateFromPLY(path.toUtf8().data(),
            &buffer[0], buffer.size());
    if(!model){
        logging("fail to read model");
        return;
    }

    logging(QString("open %1").arg(path));
    m_scene->clear();
    m_scene->addBuffer(model);
}

