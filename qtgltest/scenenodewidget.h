#pragma once
#include <QWidget>
#include <memory>


namespace Ui {
class SceneNodeWidget;
}


class SceneNode;
class SceneNodeWidget: public QWidget
{
Q_OBJECT

    std::weak_ptr<SceneNode> m_node;

public:
    SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent=0);
    ~SceneNodeWidget();

public slots:
    void onUpdate(std::shared_ptr<SceneNode> node);

private slots:
    void onValueChanged();

private:
    void updateSceneNode();

private:
    Ui::SceneNodeWidget *ui;
};

