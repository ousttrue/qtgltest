#pragma once
#include "ui_scenenodewidget.h"
#include <memory>


class SceneNode;
class SceneNodeWidget: public QWidget, Ui::SceneNodeWidget
{
Q_OBJECT

    std::weak_ptr<SceneNode> m_node;

public:
    SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent=0);

public slots:
    void onUpdate(std::shared_ptr<SceneNode> node);

private slots:
    void onValueChanged();

private:
    void updateSceneNode();
};

