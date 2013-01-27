#include "glview.h"
#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#include <QTimer>


GLView::GLView(QWidget *parent)
: QGLWidget(parent), m_scene(new OpenGLScene), m_elapsed(0)
{
    m_gl=std::make_shared<OpenGLRenderer>(m_scene);
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
    m_gl->initialize();
    m_scene->initialize();
	qglClearColor(Qt::lightGray);
}

void GLView::resizeGL(int width, int height)
{
    m_gl->resize(width, height);
}

void GLView::paintGL()
{
    m_gl->clear();
    m_gl->render();
}

