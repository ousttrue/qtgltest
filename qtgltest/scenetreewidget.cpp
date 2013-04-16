#include "scenetreewidget.h"
#include "scenemodel.h"


SceneTreeWidget::SceneTreeWidget(SceneModel *scene, QWidget *parent)
    : QTreeView(parent), m_scene(scene)
{
    setModel(m_scene);    
}

