#pragma once
#include <QAbstractItemModel>
#include <memory>


class OpenGLScene;
class SceneModel: public QAbstractItemModel
{
Q_OBJECT

    std::shared_ptr<OpenGLScene> m_openglScene;

    // mouse
    bool m_mouseLeft;
    bool m_mouseMiddle;
    bool m_mouseRight;
    int m_mouseX;
    int m_mouseY;

    // backbuffer
    int m_w;
    int m_h;

public:
    SceneModel(QObject* parent=0);
    QModelIndex index(int, int, const QModelIndex&) const;
    QModelIndex parent(const QModelIndex&) const;
    int rowCount(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int) const;

    int columnCount(const QModelIndex&) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void resize(int w, int h);

    void loadFile(const QString &path);
    std::shared_ptr<OpenGLScene> getOpenGLScene(){ return m_openglScene; }

    // mouse event
    void onMouseLeftDown(int x, int y);
    void onMouseMiddleDown(int x, int y);
    void onMouseRightDown(int x, int y);
    void onMouseLeftUp(int x, int y);
    void onMouseMiddleUp(int x, int y);
    void onMouseRightUp(int x, int y);
    void onMouseMove(int x, int y);
    void onMouseWheel(int d);

signals:
    void logging(const QString &message);
    void updated();
};
