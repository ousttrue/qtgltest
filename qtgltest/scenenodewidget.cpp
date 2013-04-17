#include "scenenodewidget.h"
#include "SceneNode.h"


SceneNodeWidget::SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent)
    : QWidget(parent), m_node(node)
{
    setupUi(this);
	updateSceneNode();
    QObject::connect(q_x, SIGNAL(valueChanged(double)),
            this, SLOT(onValueChanged()));
}

void SceneNodeWidget::onUpdate(std::shared_ptr<SceneNode> node)
{
    auto target=m_node.lock();
    if(!target){
        return;
    }
    if(node!=target){
        return;
    }
    updateSceneNode();
}

void SceneNodeWidget::onValueChanged()
{
    auto target=m_node.lock();
    if(!target){
        return;
    }
    target->setPosition(q_x->value(), q_y->value(), q_z->value());
}

void SceneNodeWidget::updateSceneNode()
{
    auto target=m_node.lock();
    if(!target){
        return;
    }
    auto &position=target->position();
    q_x->setValue(position[0]);
    q_y->setValue(position[1]);
    q_z->setValue(position[2]);
    auto &quternion=target->quaternion();
}

