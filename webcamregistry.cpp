#include "webcamregistry.h"

WebcamRegistry::WebcamRegistry(QObject *parent) : QObject(parent)
{
    webcamHosts.append(new StripchatHost(this));
    webcamHosts.append(new ChaturbateHost(this));

    Worker *worker = new Worker();
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &WebcamRegistry::startFetchingInfo, worker, &Worker::doWork);
    connect(worker, &Worker::workerFinished, this, &WebcamRegistry::handleInfoResult);

    connect(ffmpeg, &Ffmpeg::downloadStarted, this, &WebcamRegistry::downloadStarted);
    connect(ffmpeg, &Ffmpeg::downloadEnded, this, &WebcamRegistry::downloadEnded);

    workerThread.start();
}

WebcamRegistry::~WebcamRegistry()
{
    workerThread.quit();
    workerThread.wait();
}

QVariantMap WebcamRegistry::getTypes()
{
    QVariantMap result;
    QListIterator<WebcamHost*> iterator(webcamHosts);
    while (iterator.hasNext()) {
        auto host = iterator.next();
        result.insert(host->getCodeName(), host->getName());
    }

    return result;
}

QString WebcamRegistry::host()
{
    return currentHostName;
}

void WebcamRegistry::setHost(QString host)
{
    if (host != currentHostName) {
        currentHostName = host;
        emit hostChanged();
    }
}

void WebcamRegistry::fetchInfo(QString modelNameOrUrl)
{
    fetchInfo(currentHostName, modelNameOrUrl);
}

void WebcamRegistry::fetchInfo(QString host, QString modelNameOrUrl)
{
    if (modelNameOrUrl.isNull() || modelNameOrUrl.isEmpty()) {
        emit fetchingInfoFailed();
        return;
    }
    WebcamHost* currentHost = getHost(host);
    if (currentHost == nullptr) {
        emit fetchingInfoFailed();
        return;
    }

    emit startFetchingInfo(currentHost, modelNameOrUrl);
}

void WebcamRegistry::handleInfoResult(WebcamInfo webcamInfo)
{
    if (!webcamInfo.isSuccessful()) {
        emit fetchingInfoFailed();
        return;
    }
    emit results(webcamInfo.toMap());
}

void WebcamRegistry::openDirectory(QString directory)
{
    QDesktopServices::openUrl("file:///" + directory);
}

void WebcamRegistry::startDownload(QVariantMap webcamInfo, QString directory)
{
    ffmpeg->startDownload(webcamInfo, directory);
}

void WebcamRegistry::stopDownload(QString host, QString modelName)
{
    ffmpeg->stopDownload(host, modelName);
}

void WebcamRegistry::stopAllDownloads()
{
    ffmpeg->stopAllDownloads();
}

QString WebcamRegistry::getFriendlyName(QString host)
{
    QListIterator<WebcamHost*> iterator(webcamHosts);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        if (item->getCodeName() == host) {
            return item->getName();
        }
    }
    return "";
}

WebcamHost *WebcamRegistry::current()
{
    return getHost(currentHostName);
}

WebcamHost *WebcamRegistry::getHost(QString hostname)
{
    QListIterator<WebcamHost*> iterator(webcamHosts);
    while (iterator.hasNext()) {
        auto host = iterator.next();
        if (host->getCodeName() == hostname) {
            return host;
        }
    }

    return nullptr;
}
