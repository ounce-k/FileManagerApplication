#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtDebug>
#include <QMimeData>


#include "uihandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_exitButton_clicked();
    void on_folderButton_clicked();
    void on_deleteButton_clicked();
    void on_copyButton_clicked();
    void on_insertButton_clicked();
    void on_moveButton_clicked();
    void on_actionNew_folder_triggered();

private:
    UiHandler *m_uiHandler;
    FileModelHandler *m_modelHandler;

protected:
    //This function activates corresponding model when specific treeView is activated by user mouse click
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
