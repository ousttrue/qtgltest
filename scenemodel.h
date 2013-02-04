#pragma once
#include <QAbstractItemModel>
#include <memory>


class OpenGLScene;
class SceneModel: public QAbstractItemModel
{
Q_OBJECT

    std::shared_ptr<OpenGLScene> m_openglScene;

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

signals:
    void logging(const QString &message);
    void repaint();
};

