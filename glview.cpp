#include "glview.h"
#include "OpenGLWorld.h"
#include <QTimer>


GLView::GLView(QWidget *parent)
: QGLWidget(parent), m_gl(new OpenGLWorld), m_elapsed(0)
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
}

void GLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    m_gl->resize(width, height);
}

void GLView::paintGL()
{
    m_gl->clear();
    m_gl->render();
}

