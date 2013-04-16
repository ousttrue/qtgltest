#pragma once
#include <QListWidget>


class LoggingWidget :public QListWidget
{
Q_OBJECT

public:
    LoggingWidget(QWidget *parent=0);
    ~LoggingWidget();

public slots:
    void receive(const QString &log); 
};

