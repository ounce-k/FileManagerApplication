#include "filemodelhandler.h"

FileModelHandler::FileModelHandler(QString sPath, QObject *parent) : QObject(parent),
    m_activeSide(ACTIVE_SIDE::NEITHER), m_currActionType(ACTION_TYPE::NEITHER)

{
    m_modelLeft = new QFileSystemModel(this);
    m_modelLeft->setReadOnly(false);
    m_modelLeft->setRootPath(sPath);

    m_modelRight = new QFileSystemModel(this);
    m_modelRight->setReadOnly(false);
    m_modelRight->setRootPath(sPath);
}

QFileSystemModel *FileModelHandler::getLeftModel()
{
    return m_modelLeft;
}

QFileSystemModel *FileModelHandler::getRightModel()
{
    return m_modelRight;
}

void FileModelHandler::activateModel(ACTIVE_SIDE activeSide)
{
    m_activeSide = activeSide;
}

ACTIVE_SIDE FileModelHandler::getActiveSide()
{
    return m_activeSide;
}

void FileModelHandler::makeDir(QModelIndex index, QString name)
{
    if(!index.isValid())
    {
        return;
    }
    if(m_activeSide == ACTIVE_SIDE::LEFT)
    {
        m_modelLeft->mkdir(index, name);
    }
    else if(m_activeSide == ACTIVE_SIDE::RIGHT)
    {
        m_modelRight->mkdir(index, name);
    }
}

void FileModelHandler::deleteItem(QModelIndex index)
{
    if(!index.isValid())
    {
        return;
    }
    if(m_activeSide == ACTIVE_SIDE::LEFT)
    {
        m_modelLeft->remove(index);
    }
    else if(m_activeSide == ACTIVE_SIDE::RIGHT)
    {
        m_modelRight->remove(index);
    }
}

void FileModelHandler::initCopy(QModelIndex index)
{
    if(!index.isValid())
    {
        return;
    }
    m_processedSide = m_activeSide;
    m_processedIndex = index;
    m_currActionType = ACTION_TYPE::COPY;
}

void FileModelHandler::copyPath(QString src, QString dst)
{
    QDir dir(src);
    QFileInfo srcInfo(src);
    if (! dir.exists())
    {
        return;
    }
    dir.mkpath(dst + QDir::separator() + srcInfo.fileName());
    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString dst_path = dst + QDir::separator() + srcInfo.fileName();
        copyPath(src + QDir::separator() + d, dst_path);
    }
    foreach (QString f, dir.entryList(QDir::Files))
    {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + srcInfo.fileName() + QDir::separator() + f);
    }
}

void FileModelHandler::insert(QModelIndex index)
{
    if(m_currActionType == ACTION_TYPE::NEITHER)
    {
        return;
    }
    if(!index.isValid())
    {
        return;
    }
    if(m_currActionType == ACTION_TYPE::COPY)
    {
        QString filePathFrom, filePathTo;
        QFileSystemModel * processedModel, * currModel;
        if(m_processedSide == ACTIVE_SIDE::LEFT)
        {
            processedModel = m_modelLeft;
        }
        else
        {
            processedModel = m_modelRight;
        }
        if(m_activeSide == ACTIVE_SIDE::LEFT)
        {
            currModel = m_modelLeft;
        }
        else
        {
            currModel = m_modelRight;
        }
        if(processedModel->isDir(m_processedIndex))
        {
            filePathFrom = processedModel->filePath(m_processedIndex);
            filePathTo = currModel->filePath(index);
            copyPath(filePathFrom, filePathTo);
        }
        else
        {
            filePathFrom = processedModel->filePath(m_processedIndex);
            filePathTo = currModel->filePath(index);
            QFileInfo fi(filePathFrom);
            filePathTo += QDir::separator()+ fi.fileName();
            bool ret_val = QFile::copy(filePathFrom, filePathTo);
            if (!ret_val)
                    qDebug() << "Copy failed";
        }
    }
    else if(m_currActionType == ACTION_TYPE::MOVE)
    {
        QString filePathFrom, filePathTo;
        QFileSystemModel * processedModel, * currModel;
        if(m_processedSide == ACTIVE_SIDE::LEFT)
        {
            processedModel = m_modelLeft;
        }
        else
        {
            processedModel = m_modelRight;
        }
        if(m_activeSide == ACTIVE_SIDE::LEFT)
        {
            currModel = m_modelLeft;
        }
        else
        {
            currModel = m_modelRight;
        }
        if(processedModel->isDir(m_processedIndex))
        {
            filePathFrom = processedModel->filePath(m_processedIndex);
            filePathTo = currModel->filePath(index);
            copyPath(filePathFrom, filePathTo);
            processedModel->remove(m_processedIndex);
        }
        else
        {
            filePathFrom = processedModel->filePath(m_processedIndex);
            filePathTo = currModel->filePath(index);
            QFileInfo fi(filePathFrom);
            filePathTo += QDir::separator()+ fi.fileName();
            bool ret_val = QFile::copy(filePathFrom, filePathTo);
            if (ret_val)
            {
                qDebug() << "Copy succeed";
                processedModel->remove(m_processedIndex);
            }
        }
    }
    else
    {
        qDebug() << "Unsupported action type";
    }
}

void FileModelHandler::initMove(QModelIndex index)
{
    if(!index.isValid())
    {
        return;
    }
    m_processedSide = m_activeSide;
    m_processedIndex = index;
    m_currActionType = ACTION_TYPE::MOVE;
}
