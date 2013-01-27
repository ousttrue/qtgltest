#pragma once
#include <QGLWidget>
#include <memory>


class OpenGLRenderer;
class OpenGLScene;
class GLView : public QGLWidget
{
Q_OBJECT

    int m_elapsed;

    std::shared_ptr<OpenGLRenderer> m_gl;
    std::shared_ptr<OpenGLScene> m_scene;

public:
    GLView(std::shared_ptr<OpenGLScene> scene, QWidget *parent = 0);
    ~GLView();

signals:
    void logging(const QString &message);

public slots:
     void animate();

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

