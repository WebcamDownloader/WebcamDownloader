#ifndef WEBCAMHOST_H
#define WEBCAMHOST_H

#include <QObject>
#include <QString>
#include <QUrl>

#include "webcaminfo.h"

class WebcamHost : public QObject {
    Q_OBJECT
public:
    explicit WebcamHost(QObject *parent = nullptr) : QObject(parent) {}
    virtual QString getName() = 0;
    virtual QString getCodeName() = 0;
    virtual WebcamInfo getModelInfo(QString urlOrName) = 0;
};

#endif // WEBCAMHOST_H
