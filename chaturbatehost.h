#ifndef CHATURBATEHOST_H
#define CHATURBATEHOST_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QRegularExpression>

#include "webcamhost.h"

class ChaturbateHost : public WebcamHost
{
public:
    explicit ChaturbateHost(QObject *parent = nullptr);
    QString getName() override;
    QString getCodeName() override;
    WebcamInfo getModelInfo(QString urlOrName) override;
};

#endif // CHATURBATEHOST_H
