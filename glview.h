#pragma once
#include <QGLWidget>
#include <memory>


class OpenGLRenderer;
class SceneModel;
class GLView : public QGLWidget
{
Q_OBJECT

    int m_elapsed;

    std::shared_ptr<OpenGLRenderer> m_gl;
    SceneModel *m_scene;

public:
    GLView(SceneModel *scene, QWidget *parent = 0);
    ~GLView();

signals:
    void logging(const QString &message);

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

