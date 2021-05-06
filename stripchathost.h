#ifndef STRIPCHATHOST_H
#define STRIPCHATHOST_H

#include "webcamhost.h"
#include "webcaminfo.h"

#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

class StripchatHost : public WebcamHost
{
    Q_OBJECT
public:
    explicit StripchatHost(QObject *parent = nullptr);
    QString getName() override;
    QString getCodeName() override;
    WebcamInfo getModelInfo(QString urlOrName) override;
    QString getRefererBase() override;
};

#endif // STRIPCHATHOST_H
