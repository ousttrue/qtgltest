#pragma once
#include <QWidget>

namespace Ui {
class MeshWidget;
}

class MeshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshWidget(QWidget *parent = 0);
    ~MeshWidget();

private:
    Ui::MeshWidget *ui;
};

