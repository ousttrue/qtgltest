#include <QMainWindow>


class LoggingWidget;
class MainWindow: public QMainWindow
{
Q_OBJECT

    LoggingWidget *m_logging;

public:
    MainWindow(QWidget *parent=0);


private:
    void setupDock(QWidget *w, const QString &dockTitle, 
            int allow, Qt::DockWidgetArea add);
};
