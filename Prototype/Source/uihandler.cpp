#include "uihandler.h"

UiHandler::UiHandler(FileModelHandler* modelHandler, QMainWindow *parent) : QObject(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(parent);
    setModels(modelHandler);
    ui->treeViewLeft->installEventFilter(parent);
    ui->treeViewRight->installEventFilter(parent);

    ui->treeViewLeft->setDragEnabled(true);
    ui->treeViewLeft->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeViewLeft->setDefaultDropAction(Qt::DropAction::CopyAction);

    ui->treeViewRight->setDragEnabled(true);
    ui->treeViewRight->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeViewRight->setDefaultDropAction(Qt::DropAction::CopyAction);
}

void UiHandler::setModels(FileModelHandler *modelHandler)
{
    ui->treeViewLeft->setModel(modelHandler->getLeftModel());
    ui->treeViewRight->setModel(modelHandler->getRightModel());
    ui->treeViewLeft->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeViewRight->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

ACTIVE_SIDE UiHandler::getActiveSide(QObject *treeObj)
{
    if(treeObj == ui->treeViewLeft)
    {
        qDebug() << "Left tree is active";
        return ACTIVE_SIDE::LEFT;
    }
    else if(treeObj == ui->treeViewRight)
    {
        qDebug() << "Right tree is active";
        return ACTIVE_SIDE::RIGHT;
    }
    return ACTIVE_SIDE::NEITHER;
}

QModelIndex UiHandler::getModelIndex(ACTIVE_SIDE activeSide)
{
    if(activeSide == ACTIVE_SIDE::LEFT)
    {
        return ui->treeViewLeft->currentIndex();
    }
    else if(activeSide == ACTIVE_SIDE::RIGHT)
    {
        return ui->treeViewRight->currentIndex();
    }
    else
    {
        return QModelIndex();
    }
}

bool UiHandler::isDeletingConfirmed()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(ui->centralwidget, "Delete",
                             "Do you want to delete selected item?",
                             QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UiHandler::isSameNameCopyConfirmed()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(ui->centralwidget, "Copy",
                             "Do you want to copy selected item?",
                             QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

