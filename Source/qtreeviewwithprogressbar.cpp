#include "qtreeviewwithprogressbar.h"
#include <QDebug>
#include <QMimeData>
#include <QDropEvent>
#include <QDirModel>

QTreeViewWithProgressBar::QTreeViewWithProgressBar()
{

}

QTreeViewWithProgressBar::QTreeViewWithProgressBar(QWidget *parent): QTreeView(parent)
{

}

void QTreeViewWithProgressBar::setModelHandler(FileModelHandler *model)
{
    m_modelHandler = model;
}

void QTreeViewWithProgressBar::setSide(ACTIVE_SIDE side)
{
    m_side = side;
}

void QTreeViewWithProgressBar::dropEvent(QDropEvent *e)
{
    QModelIndex index =  this->indexAt(e->pos());
    if(!index.isValid())
    {
        return;
    }

    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
        m_modelHandler->moveDragAndDrop(
                    m_modelHandler->getIndexByFilePath(fileName),
                    index,
                    m_side);
    }
}

