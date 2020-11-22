#ifndef QTREEVIEWWITHPROGRESSBAR_H
#define QTREEVIEWWITHPROGRESSBAR_H

#include <QObject>
#include <QTreeView>
#include "filemodelhandler.h"

class QTreeViewWithProgressBar : public QTreeView
{
    Q_OBJECT

public:
    QTreeViewWithProgressBar();
    QTreeViewWithProgressBar(QWidget *parent);
    void setModelHandler(FileModelHandler* model);
    void setSide(ACTIVE_SIDE side);

protected:
    void dropEvent(QDropEvent *e) override;

private:
    FileModelHandler* m_modelHandler;
    ACTIVE_SIDE m_side;
};

#endif // QTREEVIEWWITHPROGRESSBAR_H
