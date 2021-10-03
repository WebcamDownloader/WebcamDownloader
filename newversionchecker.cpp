#include "newversionchecker.h"

NewVersionChecker::NewVersionChecker(QObject *parent) : QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::finished, this, &NewVersionChecker::onLatestVersionReceived);
}

void NewVersionChecker::checkForNewVersion()
{
    QNetworkRequest request(QUrl("https://github.com/WebcamDownloader/WebcamDownloader/releases/latest"));
    manager.get(request);
}

void NewVersionChecker::onLatestVersionReceived(QNetworkReply *reply)
{
    auto locationHeader = reply->header(QNetworkRequest::KnownHeaders::LocationHeader);
    reply->deleteLater();

    auto latestVersion = QVersionNumber::fromString(locationHeader.toUrl().path().toUtf8().split('/').last().replace('v', ""));
    if (latestVersion > currentVersion()) {
        emit newVersionFound(latestVersion.toString());
    }
}

QVersionNumber NewVersionChecker::currentVersion()
{
    return QVersionNumber::fromString("0.4.0");
}
