#include "worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::doWork(WebcamHost *host, QString modelNameOrUrl)
{
    emit workerFinished(host->getModelInfo(modelNameOrUrl));
}
