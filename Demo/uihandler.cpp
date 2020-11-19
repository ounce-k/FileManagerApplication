#include "uihandler.h"

#include "progressbarhandler.h"

UiHandler::UiHandler(FileModelHandler* modelHandler, QMainWindow *parent) : QObject(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(parent);
    setModels(modelHandler);
    ui->treeViewLeft->installEventFilter(parent);
    ui->treeViewRight->installEventFilter(parent);

    ui->treeViewLeft->setModelHandler(modelHandler);
    ui->treeViewRight->setModelHandler(modelHandler);

    ui->treeViewLeft->setSortingEnabled(true);
    ui->treeViewRight->setSortingEnabled(true);

    ui->treeViewLeft->setSide(ACTIVE_SIDE::LEFT);
    ui->treeViewRight->setSide(ACTIVE_SIDE::RIGHT);

    ui->actionShowDate->setCheckable(true);
    ui->actionShowSize->setCheckable(true);
    ui->actionShowType->setCheckable(true);
    ui->actionShowDate->setChecked(true);
    ui->actionShowSize->setChecked(true);
    ui->actionShowType->setChecked(true);

    ui->treeViewLeft->setDragEnabled(true);
    ui->treeViewLeft->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeViewLeft->setDefaultDropAction(Qt::DropAction::MoveAction);

    ui->treeViewLeft->setDropIndicatorShown(true);
    ui->treeViewRight->setDropIndicatorShown(true);

    ui->treeViewRight->setDragEnabled(true);
    ui->treeViewRight->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeViewRight->setDefaultDropAction(Qt::DropAction::MoveAction);
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

void UiHandler::setAttributeShown(ATTRIBUTE_NAME name)
{
    switch(name)
    {
        case ATTRIBUTE_NAME::DATE:
        ui->treeViewLeft->setColumnHidden(3, !ui->actionShowDate->isChecked());
        ui->treeViewRight->setColumnHidden(3, !ui->actionShowDate->isChecked());
        break;
        case ATTRIBUTE_NAME::SIZE:
        ui->treeViewLeft->setColumnHidden(1, !ui->actionShowSize->isChecked());
        ui->treeViewRight->setColumnHidden(1, !ui->actionShowSize->isChecked());
        break;
        case ATTRIBUTE_NAME::TYPE:
        ui->treeViewLeft->setColumnHidden(2, !ui->actionShowType->isChecked());
        ui->treeViewRight->setColumnHidden(2, !ui->actionShowType->isChecked());
        break;
    }
}

void UiHandler::progressBarStart(QString operationame, int operationIndex)
{
    ProgressBarHandler *timer = new ProgressBarHandler(operationame);
    timer->show();
    progressBarMap.insert(operationIndex, timer);
}

void UiHandler::progressBarEnd(int operationIndex)
{
    progressBarMap[operationIndex]->close();
    delete progressBarMap[operationIndex];
    progressBarMap.remove(operationIndex);
}

void UiHandler::progressBarUpdate(int operationIndex, int progressValue)
{
     progressBarMap[operationIndex]->updateProgress(progressValue);
}


