#include "stripchathost.h"

#include <QJsonArray>

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

    QUrl searchUrl("https://stripchat.com/api/front/v4/models/search/suggestion?query=" + username.toLower() + "&limit=1&primaryTag=girls&uniq=" + randomString());
    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QNetworkRequest searchRequest(searchUrl);
    searchRequest.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, userAgentGenerator.getRandomUserAgent());
    searchRequest.setRawHeader("Referer", "https://stripchat.com");
    searchRequest.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);
    auto searchReply = manager.get(searchRequest);
    connect(searchReply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    searchReply->deleteLater();

    auto document = QJsonDocument::fromJson(searchReply->readAll()).object();
    auto models = document.value("models").toArray();
    if (models.size() < 1) {
        return WebcamInfo(getCodeName(), username, false, QUrl(), true);
    }
    auto model = models.at(0).toObject();
    if (model.value("username").toString() != username) {
        return WebcamInfo(getCodeName(), username, false, QUrl(), true);
    }

    auto id = model.value("id").toInt();
    auto name = model.value("username").toString();
    auto available = model.value("isOnline").toBool();

    QNetworkRequest initializeRequest(QUrl("https://stripchat.com/api/front/v3/config/initial?timezoneOffset=-60&timezone=Europe%2FPrague&requestPath=%2F" + username + "&defaultTag=girls"));
    initializeRequest.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, userAgentGenerator.getRandomUserAgent());
    initializeRequest.setRawHeader("Referer", "https://stripchat.com");
    initializeRequest.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);
    auto initializeReply = manager.get(initializeRequest);
    connect(initializeReply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    initializeReply->deleteLater();

    auto initializeDocument = QJsonDocument::fromJson(initializeReply->readAll()).object();
    auto common = initializeDocument.value("initial").toObject().value("common").toObject();
    auto urlTemplate = common.value("hlsStreamUrlTemplate").toString();
    const auto defaultHost = common.value("defaultHlsStreamHost").toString();
    const auto streamUrl = urlTemplate
        .replace("{cdnHost}", defaultHost)
        .replace("{streamName}", QString::number(id))
        .replace("{suffix}", "_auto")
    ;

    return WebcamInfo(getCodeName(), name, available, streamUrl, name.isEmpty());
}

QString StripchatHost::getRefererBase()
{
    return "https://stripchat.com/";
}

const QString StripchatHost::randomString()
{
    constexpr int length = 16;

    const QString charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    QString result;
    result.reserve(length);

    QRandomGenerator *random = QRandomGenerator::global();

    for (int i = 0; i < length; ++i) {
        int index = random->bounded(charset.size());
        result.append(charset.at(index));
    }

    return result;
}
