#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QObject>
#include <QDebug>
#include <QtWidgets>
#include "ui_mainwindow.h"
#include "filemodelhandler.h"


class UiHandler : public QObject
{
    Q_OBJECT
public:
    explicit UiHandler(FileModelHandler* modelHandler, QMainWindow *parent);
    ACTIVE_SIDE getActiveSide(QObject *treeObj);
    QModelIndex getModelIndex(ACTIVE_SIDE activeSide);
    //This function gets confirmation of deletion item from user using QMessageBox
    bool isDeletingConfirmed();
    //This function gets confirmation of copy files with the same name from user using QMessageBox
    bool isSameNameCopyConfirmed();

private:
    Ui::MainWindow *ui;
    //This function sets specific models to the corresponding treeViews
    void setModels(FileModelHandler* modelHandler);
};

#endif // UIHANDLER_H
