#include <QApplication>
#include "mainwindow.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow w;
    w.resize(640, 480);
    w.show();

    return app.exec();
}

