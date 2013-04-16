#include "glview.h"
#include "OpenGLRenderer.h"
#include "scenemodel.h"
#include "OpenGLScene.h"
#include <QTimer>
#include <QMouseEvent>


GLView::GLView(SceneModel *scene, QWidget *parent)
: QGLWidget(parent), m_elapsed(0), m_gl(new OpenGLRenderer), m_scene(scene)
{
    QObject::connect(m_scene, SIGNAL(updated()), this, SLOT(repaint()));
}

GLView::~GLView()
{
}

void GLView::initializeGL()
{
    if(!m_gl->initialize()){
        //logging("fail to OpenGLRenderer::initialize");
        while(m_gl->hasLogMessage()){
			logging(m_gl->dequeueLogMessage().c_str());
        }
        return;
    }
	qglClearColor(Qt::lightGray);
}

void GLView::resizeGL(int width, int height)
{
    m_scene->resize(width, height);
    m_gl->resize(width, height);
}

void GLView::paintGL()
{
    m_gl->render(m_scene->getOpenGLScene());
}

void GLView::mouseMoveEvent(QMouseEvent *event)
{
    m_scene->onMouseMove(event->x(), event->y());
}

void GLView::mousePressEvent(QMouseEvent *event)
{
    auto b=event->button();
    if(b==Qt::LeftButton){
        m_scene->onMouseLeftDown(event->x(), event->y());
    }
    else if(b==Qt::MidButton){
        m_scene->onMouseMiddleDown(event->x(), event->y());
    }
    else if(b==Qt::RightButton){
        m_scene->onMouseRightDown(event->x(), event->y());
    }
}

void GLView::mouseReleaseEvent(QMouseEvent *event)
{
    auto b=event->button();
    if(b==Qt::LeftButton){
        m_scene->onMouseLeftUp(event->x(), event->y());
    }
    else if(b==Qt::MidButton){
        m_scene->onMouseMiddleUp(event->x(), event->y());
    }
    else if(b==Qt::RightButton){
        m_scene->onMouseRightUp(event->x(), event->y());
    }
}

void GLView::wheelEvent(QWheelEvent *event)
{
    m_scene->onMouseWheel(event->delta());
}

