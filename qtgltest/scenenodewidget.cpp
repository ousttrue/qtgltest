#include "scenenodewidget.h"


SceneNodeWidget::SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent)
    : QWidget(parent), m_node(node)
{
}

