#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QObject>
#include <QDebug>
#include <QtWidgets>
#include "ui_mainwindow.h"
#include "filemodelhandler.h"
#include "progressbarhandler.h"

enum class ATTRIBUTE_NAME
{
    SIZE,
    DATE,
    TYPE
};

class UiHandler : public QObject
{
    Q_OBJECT

public:
    explicit UiHandler(FileModelHandler* modelHandler, QMainWindow *parent);
    ACTIVE_SIDE getActiveSide(QObject *treeObj);
    QModelIndex getModelIndex(ACTIVE_SIDE activeSide);
    //This function gets confirmation of deletion item from user using QMessageBox
    bool isDeletingConfirmed();
    //hides or shows column, clicked by user
    void setAttributeShown(ATTRIBUTE_NAME name);

public slots:
    void progressBarStart(QString operationame, int operationIndex);
    void progressBarEnd(int operationIndex);
    void progressBarUpdate(int operationIndex, int progressValue);

private:
    Ui::MainWindow *ui;
    //This function sets specific models to the corresponding treeViews
    void setModels(FileModelHandler* modelHandler);
    QMap<int, ProgressBarHandler*> progressBarMap;
};

#endif // UIHANDLER_H
