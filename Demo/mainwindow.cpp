#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_modelHandler = new FileModelHandler("", this);
    m_uiHandler = new UiHandler(m_modelHandler, this);

    connect(m_modelHandler, SIGNAL(operationStart(QString, int)), m_uiHandler, SLOT(progressBarStart(QString, int)));
    connect(m_modelHandler, SIGNAL(operationEnd(int)), m_uiHandler, SLOT(progressBarEnd(int)));
    connect(m_modelHandler, SIGNAL(operationUpdate(int, int)), m_uiHandler, SLOT(progressBarUpdate(int, int)));
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

void MainWindow::on_actionNewFolder_triggered()
{
    QModelIndex index = m_uiHandler->getModelIndex(m_modelHandler->getActiveSide());
    QString name = QInputDialog::getText(this, "New folder name", "Enter the folder name:");
    if(name.isEmpty()) return;
    m_modelHandler->makeDir(index, name);
}

void MainWindow::on_actionShowDate_triggered()
{
    m_uiHandler->setAttributeShown(ATTRIBUTE_NAME::DATE);
}

void MainWindow::on_actionShowType_triggered()
{
    m_uiHandler->setAttributeShown(ATTRIBUTE_NAME::TYPE);
}

void MainWindow::on_actionShowSize_triggered()
{
    m_uiHandler->setAttributeShown(ATTRIBUTE_NAME::SIZE);
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




