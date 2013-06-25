#include "scenenodewidget.h"
#include "SceneNode.h"
#include "ui_scenenodewidget.h"


SceneNodeWidget::SceneNodeWidget(std::shared_ptr<SceneNode> node, QWidget *parent)
    : QWidget(parent), m_node(node),
    ui(new Ui::SceneNodeWidget)
{
    ui->setupUi(this);

	updateSceneNode();
    QObject::connect(ui->q_x, SIGNAL(valueChanged(double)),
            this, SLOT(onValueChanged()));
    QObject::connect(ui->q_y, SIGNAL(valueChanged(double)),
            this, SLOT(onValueChanged()));
    QObject::connect(ui->q_z, SIGNAL(valueChanged(double)),
            this, SLOT(onValueChanged()));
}

SceneNodeWidget::~SceneNodeWidget()
{
    delete ui;
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
    target->setPosition(ui->q_x->value(), ui->q_y->value(), ui->q_z->value());
}

void SceneNodeWidget::updateSceneNode()
{
    auto target=m_node.lock();
    if(!target){
        return;
    }
    auto &position=target->position();
    ui->q_x->setValue(position[0]);
    ui->q_y->setValue(position[1]);
    ui->q_z->setValue(position[2]);
    auto &quternion=target->quaternion();

    auto mesh=target->getMesh();
    if(mesh){
        ui->meshWidget->show();
    }
    else{
        ui->meshWidget->hide();
    }
    auto camera=target->getCamera();
    if(camera){
        ui->cameraWidget->show();
    }
    else{
        ui->cameraWidget->hide();
    }
    auto light=target->getLight();
    if(light){
        ui->lightWidget->show();
    }
    else{
        ui->lightWidget->hide();
    }
}
