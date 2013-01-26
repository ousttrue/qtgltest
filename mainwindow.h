#include <QMainWindow>


class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent=0);


private:
    void setupDock(QWidget *w, const QString &dockTitle, 
            int allow, Qt::DockWidgetArea add);
};

