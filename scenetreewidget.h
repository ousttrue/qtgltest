#include <QTreeView>


class SceneTreeWidget: public QTreeView
{
Q_OBJECT

public:
    SceneTreeWidget(QWidget *parent=0);

signals:
    void logging(const QString &message);

};

