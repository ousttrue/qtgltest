#include <QMainWindow>
#include <memory>


class LoggingWidget;
class SceneModel;
class SceneTreeWidget;;
class QModelIndex;
class MainWindow: public QMainWindow
{
Q_OBJECT

    LoggingWidget *m_logging;
    SceneModel *m_scene;
    SceneTreeWidget *m_sceneTreeView;

public:
    MainWindow(QWidget *parent=0);

signals:
    void logging(const QString &message);

private slots:
    void onOpen();
    void onSceneItemActivated(const QModelIndex &index);

private:
    void setupDock(QWidget *w, const QString &dockTitle, 
            int allow, Qt::DockWidgetArea add);
};

