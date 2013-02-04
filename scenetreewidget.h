#include <QTreeView>


class SceneModel;
class SceneTreeWidget: public QTreeView
{
Q_OBJECT

    SceneModel *m_scene;

public:
    SceneTreeWidget(SceneModel *scene, QWidget *parent=0);

signals:
    void logging(const QString &message);

};

