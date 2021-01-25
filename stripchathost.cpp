#include "stripchathost.h"

StripchatHost::StripchatHost(QObject *parent) : WebcamHost(parent)
{

}

QString StripchatHost::getName()
{
    return "Stripchat";
}

QString StripchatHost::getCodeName()
{
    return "stripchat";
}

WebcamInfo StripchatHost::getModelInfo(QString urlOrName)
{
    QString username;
    if (urlOrName.startsWith("stripchat.com")) {
        urlOrName = "https://" + urlOrName;
    }

    if (urlOrName.startsWith("http")) {
        QRegularExpression regex("https://(?:[a-z]{2}\\.)?stripchat\\.com/(.+?)(?:\\?|$)");
        QRegularExpressionMatch match = regex.match(urlOrName);
        if (!match.hasMatch()) {
            return WebcamInfo();
        }
        username = match.captured(1);
    } else {
        username = urlOrName;
    }
    QUrl detailsUrl("https://stripchat.com/api/front/v2/models/username/" + username + "/cam");

    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QNetworkRequest request(detailsUrl);
    request.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, userAgentGenerator.getRandomUserAgent());
    request.setRawHeader("Referer", "https://stripchat.com");
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);
    auto reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    reply->deleteLater();

    auto document = QJsonDocument::fromJson(reply->readAll()).object();
    auto id = document.value("cam").toObject().value("streamName").toString();
    auto name = document.value("user").toObject().value("user").toObject().value("login").toString();
    auto hlsServer = document
            .value("cam")
            .toObject()
            .value("viewServers")
            .toObject()
            .value("flashphoner-hls")
            .toString();
    auto streamUrl = QString("https://b-%1.stripst.com/hls/%2/%2.m3u8")
            .arg(hlsServer)
            .arg(id);
    auto available = document.value("cam").toObject().value("isCamAvailable").toBool();
    return WebcamInfo(getCodeName(), name, available, streamUrl, name.isEmpty());
}
