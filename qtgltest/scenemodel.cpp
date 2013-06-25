#include "scenemodel.h"
#include "OpenGLScene.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"
#include "Camera.h"
#include <QFile>
#include <QFileInfo>
#include <QDataStream>


SceneModel::SceneModel(QObject *parent)
    : QAbstractItemModel(parent), m_openglScene(new OpenGLScene)
    , m_mouseLeft(false), m_mouseMiddle(false), m_mouseRight(false),
    m_mouseX(0), m_mouseY(0),
    m_w(1), m_h(1)
{
}

// columns
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

// rows
int SceneModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() && parent.column()!=0){
        return 0;
    }
    auto parentItem=itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

QVariant SceneModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.column()<0 || index.column()>0){
        return QVariant();
    }
    if(auto item=itemForIndex(index)){
        if(role==Qt::DisplayRole||role==Qt::EditRole){
            return item->name().c_str();
        }
    }
    return QVariant();
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex &parent) const
{
    if(row<0 || column <0 ||column>0
            || (parent.isValid() && parent.column()!=0)){
        return QModelIndex();
    }
    auto parentItem=itemForIndex(parent);
    Q_ASSERT(parentItem);
    if(auto item=parentItem->childAt(row)){
        return createIndex(row, column, item.get());
    }
    return QModelIndex();
}

QModelIndex SceneModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()){
        return QModelIndex();
    }
    if(auto childItem=itemForIndex(index)){
        if(auto parentItem=childItem->parent()){
            if(parentItem==m_openglScene->getRootNode()){
                return QModelIndex();
            }
            if(auto grandParentItem=parentItem->parent()){
                int row=grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem.get());
            }
        }
    }
    return QModelIndex();
}

bool SceneModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    endInsertRows();
    return true;
}

bool SceneModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
	if(auto item=parent.isValid() ? static_cast<SceneNode*>(parent.internalPointer()) : m_openglScene->getRootNode().get()){
		item->removeChildren(row, count);
	}
    endInsertRows();
    return true;
}

void SceneModel::resize(int w, int h)
{
    m_w=w;
    m_h=h;
    m_openglScene->getCamera()->resize(w, h);
    updated();
}

void SceneModel::loadFile(const QString &path)
{
    QFile file(path);
    std::vector<char> buffer(file.size());
    if(buffer.empty()){
        logging("empty file");
        return;
    }

	if (!file.open(QIODevice::ReadOnly)){
		logging("fail to open");
		return;
	}

    QDataStream in(&file);
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

    auto modelNode=std::make_shared<SceneNode>(path.toUtf8().data());
    modelNode->setMesh(model);
    m_openglScene->getRootNode()->addChild(modelNode);
    insertRow(0, QModelIndex());

    updated();
}

void SceneModel::onMouseLeftDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseLeft=true;
}

void SceneModel::onMouseMiddleDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseMiddle=true;
}

void SceneModel::onMouseRightDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseRight=true;
}

void SceneModel::onMouseLeftUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseLeft=false;
}

void SceneModel::onMouseMiddleUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseMiddle=false;
}

void SceneModel::onMouseRightUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseRight=false;
}

void SceneModel::onMouseMove(int x, int y)
{
    bool repaint=false;
    int dx=x-m_mouseX;
    int dy=y-m_mouseY;
    m_mouseX=x;
    m_mouseY=y;
    if(m_mouseLeft){
    }
    if(m_mouseMiddle){
        float min=m_w<m_h ? m_w : m_h;
        float ratio=1.0f/min;
        m_openglScene->getCamera()->shift(dx*ratio, -dy*ratio);
        repaint=true;
    }
    if(m_mouseRight){
        float min=m_w<m_h ? m_w : m_h;
        float ratio=14000.0f/min;
        m_openglScene->getCamera()->head(dx*ratio);
        m_openglScene->getCamera()->pitch(dy*ratio);
        repaint=true;
    }
    if(repaint){
        updated();
    }
}

void SceneModel::onMouseWheel(int d)
{
    m_openglScene->getCamera()->dolly(d);
    updated();
}

std::shared_ptr<SceneNode> SceneModel::itemForIndex(const QModelIndex &index)const
{
    if(index.isValid()){
        if(auto item=static_cast<SceneNode*>(index.internalPointer())){
            return item->shared_from_this();
        }
    }
    return m_openglScene->getRootNode();
}

