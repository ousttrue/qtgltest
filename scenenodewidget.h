#pragma once
#include <QWidget>
#include <memory>


class SceneNode;
class SceneNodeWidget: public QWidget
{
    std::weak_ptr<SceneNode> m_node;

public:
    SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent=0);
};

