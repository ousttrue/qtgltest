#include "scenemodel.h"
#include "OpenGLScene.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"
#include <QFileInfo>
#include <QDataStream>


SceneModel::SceneModel(QObject *parent)
    : QAbstractItemModel(parent), m_openglScene(new OpenGLScene)
{
}

QModelIndex SceneModel::index(int, int, const QModelIndex&) const
{
    return QModelIndex();
}

QModelIndex SceneModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int SceneModel::rowCount(const QModelIndex&) const
{
    return 0;
}

int SceneModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section==0){
        return QString("name");
    }

    return QVariant();
}

QVariant SceneModel::data(const QModelIndex&, int) const
{
    return QVariant();
}

void SceneModel::resize(int w, int h)
{
    m_openglScene->resize(w, h);
    repaint();
}

void SceneModel::loadFile(const QString &path)
{
    QFileInfo file(path);
    std::vector<char> buffer(file.size());
    if(buffer.empty()){
        logging("empty file");
        return;
    }

    QDataStream in(path.toLocal8Bit());
    if(in.readRawData(&buffer[0], buffer.size())==-1){
        logging("fail to read file");
        return;
    }

    QFileInfo info(path);
    QString ext=info.suffix().toLower();
    std::shared_ptr<IndexedVertexBuffer> model;
    if(ext=="ply"){
        model=IndexedVertexBuffer::CreateFromPLY(path.toUtf8().data(),
                &buffer[0], buffer.size());
    }
    else if(ext=="pmd"){
        model=IndexedVertexBuffer::CreateFromPMD(path.toUtf8().data(),
                &buffer[0], buffer.size());
	}
    else{
        logging(QString("unknown extension: %1").arg(ext));
        return;
    }

    if(!model){
        logging("fail to read model");
        return;
    }

    logging(QString("open %1").arg(path));
    m_openglScene->clear();
    m_openglScene->getRootNode()->addChild(path.toUtf8().data(), model);

    // ToDo:
    repaint();
}

