#pragma once
#include <QWidget>

namespace Ui {
class LightWidget;
}

class LightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = 0);
    ~LightWidget();

private:
    Ui::LightWidget *ui;
};

