#include "glview.h"
#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#include <QTimer>


GLView::GLView(std::shared_ptr<OpenGLScene> scene, QWidget *parent)
: QGLWidget(parent), m_scene(scene), m_elapsed(0)
{
    m_gl=std::make_shared<OpenGLRenderer>();
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

