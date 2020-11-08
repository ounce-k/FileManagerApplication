#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_modelHandler = new FileModelHandler("", this);
    m_uiHandler = new UiHandler(m_modelHandler, this);

}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_folderButton_clicked()
{
    QModelIndex index = m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    QString name = QInputDialog::getText(this, "New folder name", "Enter the folder name:");
    if(name.isEmpty()) return;
    m_modelHandler->makeDir(index, name);
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex index =  m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    if(m_uiHandler->isDeletingConfirmed())
    {
        m_modelHandler->deleteItem(index);
    }
}

void MainWindow::on_copyButton_clicked()
{
    QModelIndex index =  m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    m_modelHandler->initCopy(index);
}

void MainWindow::on_insertButton_clicked()
{
    QModelIndex index =  m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    m_modelHandler->insert(index);
}

void MainWindow::on_moveButton_clicked()
{
    QModelIndex index =  m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    m_modelHandler->initMove(index);
}

void MainWindow::on_actionNew_folder_triggered()
{
    QModelIndex index = m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    QString name = QInputDialog::getText(this, "New folder name", "Enter the folder name:");
    if(name.isEmpty()) return;
    m_modelHandler->makeDir(index, name);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        m_modelHandler->activateModel(m_uiHandler->getActiveSide(obj));
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}




