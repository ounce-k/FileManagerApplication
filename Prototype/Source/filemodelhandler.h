#ifndef FILEMODELHANDLER_H
#define FILEMODELHANDLER_H

#include <QObject>
#include <QFileSystemModel>
#include <QDebug>

enum class ACTIVE_SIDE
{
    LEFT,
    RIGHT,
    NEITHER
};

enum class ACTION_TYPE
{
    COPY,
    MOVE,
    NEITHER
};

class FileModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileModelHandler(QString sPath = "", QObject *parent = nullptr);
    QFileSystemModel * getLeftModel();
    QFileSystemModel * getRightModel();
    //This function sets m_activeSide according to current active side, chosen by user, retrieved from m_uiHandler
    void activateModel(ACTIVE_SIDE activeSide);
    ACTIVE_SIDE getActiveSide();
    void makeDir(QModelIndex index, QString name);
    void deleteItem(QModelIndex index);
    //Memorizes the type of operation (copy), index of proceeded file and current side, where is the chosen file
    void initCopy(QModelIndex index);
    void insert(QModelIndex index);
    //Memorizes the type of operation (move), index of proceeded file and current side, where is the chosen file
    void initMove(QModelIndex index);
    void copyPath(QString src, QString dst);

private:
    QFileSystemModel *m_modelLeft;
    QFileSystemModel *m_modelRight;
    ACTIVE_SIDE m_activeSide;

    ACTION_TYPE m_currActionType;
    QModelIndex m_processedIndex;
    ACTIVE_SIDE m_processedSide;
};

#endif // FILEMODELHANDLER_H
