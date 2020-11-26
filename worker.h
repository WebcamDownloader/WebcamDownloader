#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "webcamhost.h"
#include "webcaminfo.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
public slots:
    void doWork(WebcamHost *host, QString modelNameOrUrl);
signals:
    void workerFinished(WebcamInfo webcamInfo);
};

#endif // WORKER_H
