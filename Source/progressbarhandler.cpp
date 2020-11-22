#include <QLayout>
#include "progressbarhandler.h"

ProgressBarHandler::ProgressBarHandler(QString str, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *lable = new QLabel(str);
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    layout->addWidget(lable);
    layout->addWidget(progressBar);
    setLayout(layout);

    setWindowTitle(tr("Timer"));
    resize(200, 200);
}

void ProgressBarHandler::updateProgress(int updateValue)
{
    progressBar->setValue(progressBar->value()+updateValue);
}
