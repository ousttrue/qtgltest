#include "loggingwidget.h"


LoggingWidget::LoggingWidget(QWidget *parent)
    : QListWidget(parent)
{
}

LoggingWidget::~LoggingWidget()
{
}

void LoggingWidget::receive(const QString &log)
{
    addItem(log);
    scrollToBottom();
}

