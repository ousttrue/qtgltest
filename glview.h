#pragma once
#include <QGLWidget>
#include <memory>


class OpenGLRenderer;
class GLView : public QGLWidget
{
Q_OBJECT

    int m_elapsed;

    std::shared_ptr<OpenGLRenderer> m_gl;

public:
    GLView(QWidget *parent = 0);
    ~GLView();

public slots:
     void animate();

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
};
