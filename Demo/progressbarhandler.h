#ifndef PROGRESSBARHANDLER_H
#define PROGRESSBARHANDLER_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>
#include <QLabel>

class ProgressBarHandler : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBarHandler(QString str, QWidget *parent = nullptr);

public slots:
    void updateProgress(int updateValue);

private:
    QProgressBar *progressBar;
};

#endif // PROGRESSBARHANDLER_H
