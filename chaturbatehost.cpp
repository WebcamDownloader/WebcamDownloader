#include "chaturbatehost.h"

ChaturbateHost::ChaturbateHost(QObject *parent) : WebcamHost(parent)
{

}

QString ChaturbateHost::getName()
{
    return "Chaturbate";
}

QString ChaturbateHost::getCodeName()
{
    return "chaturbate";
}

WebcamInfo ChaturbateHost::getModelInfo(QString urlOrName)
{
    QString modelUrl;
    QString modelName;

    if (urlOrName.startsWith("chaturbate.com")) {
        urlOrName = "https://" + urlOrName;
    }

    if (!urlOrName.startsWith("http")) {
        modelUrl = "https://chaturbate.com/" + urlOrName + "/";
        modelName = urlOrName;
    } else {
        QRegularExpression regex("https://(?:[a-z]{2,}\\.)?chaturbate\\.com/(.+?)(?:\\?|$|/)");
        QRegularExpressionMatch match = regex.match(urlOrName);
        if (!match.hasMatch()) {
            return WebcamInfo();
        }
        modelName = match.captured(1);
        modelUrl = urlOrName;
    }

    QUrl url(modelUrl);

    QEventLoop eventLoop;
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, userAgentGenerator.getRandomUserAgent());
    request.setRawHeader("Referer", "https://chaturbate.com/");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    auto reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    reply->deleteLater();

    auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 300) {
        return WebcamInfo();
    }

    QString sourceCode = reply->readAll();
    QStringList lines = sourceCode.split("\n");
    QListIterator<QString> iterator(lines);
    QString line;
    bool found = false;
    while (iterator.hasNext()) {
        line = iterator.next();
        if (!line.contains("m3u8")) {
            continue;
        }
        found = true;
        break;
    }
    if (!found) {
        return WebcamInfo(getCodeName(), modelName, false, QUrl(), false);
    }

    QRegExp rx("(\\\\u[0-9a-fA-F]{4})");
    int pos = 0;
    while ((pos = rx.indexIn(line, pos)) != -1) {
        line.replace(pos++, 6, QChar(rx.cap(1).right(4).toUShort(0, 16)));
    }

    QString streamUrl;
    QStringList parts = line.split("\"");
    iterator = QListIterator<QString>(parts);
    while (iterator.hasNext()) {
        auto part = iterator.next();
        if (!part.contains("m3u8")) {
            continue;
        }
        streamUrl = part;
        break;
    }
    if (streamUrl.isEmpty()) {
        return WebcamInfo(getCodeName(), modelName, false, QUrl(), false);
    }

    return WebcamInfo(getCodeName(), modelName, true, streamUrl, false);
}
