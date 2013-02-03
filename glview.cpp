#include "glview.h"
#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#include <QTimer>
#include <QMouseEvent>


GLView::GLView(std::shared_ptr<OpenGLScene> scene, QWidget *parent)
: QGLWidget(parent), m_elapsed(0), m_gl(new OpenGLRenderer), m_scene(scene)
{
}

GLView::~GLView()
{
}

void GLView::animate()
{
    m_elapsed = (m_elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
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
    m_gl->render(m_scene);
}

void GLView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_scene->onMouseMove(event->x(), event->y())){
        repaint();
    }
}

void GLView::mousePressEvent(QMouseEvent *event)
{
    auto b=event->button();
    if(b==Qt::LeftButton){
        if(m_scene->onMouseLeftDown(event->x(), event->y())){
            repaint();
        }
    }
    else if(b==Qt::MidButton){
        if(m_scene->onMouseMiddleDown(event->x(), event->y())){
            repaint();
        }
    }
    else if(b==Qt::RightButton){
        if(m_scene->onMouseRightDown(event->x(), event->y())){
            repaint();
        }
    }
}

void GLView::mouseReleaseEvent(QMouseEvent *event)
{
    auto b=event->button();
    if(b==Qt::LeftButton){
        if(m_scene->onMouseLeftUp(event->x(), event->y())){
            repaint();
        }
    }
    else if(Qt::MidButton){
        if(m_scene->onMouseMiddleUp(event->x(), event->y())){
            repaint();
        }
    }
    else if(Qt::RightButton){
        if(m_scene->onMouseRightUp(event->x(), event->y())){
            repaint();
        }
    }
}

void GLView::wheelEvent(QWheelEvent *event)
{
    if(m_scene->onMouseWheel(event->delta())){
        repaint();
    }
}

