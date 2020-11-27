#ifndef WEBCAMREGISTRY_H
#define WEBCAMREGISTRY_H

#include <QObject>
#include <QVariantMap>
#include <QThread>
#include <QByteArray>
#include <QStandardPaths>
#include <QDesktopServices>

#include "webcamhost.h"
#include "stripchathost.h"
#include "chaturbatehost.h"
#include "worker.h"
#include "ffmpeg.h"

class WebcamRegistry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap types READ getTypes CONSTANT)
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
public:
    explicit WebcamRegistry(QObject *parent = nullptr);
    ~WebcamRegistry();
    QVariantMap getTypes();
    QString host();
    void setHost(QString host);
signals:
    void hostChanged();
    void fetchingInfoFailed();
    void startFetchingInfo(WebcamHost *host, QString modelNameOrUrl);
    void results(QVariantMap result);
    void downloadStarted(QString host, QString modelName);
    void downloadEnded(QString host, QString modelName);

public slots:
    void fetchInfo(QString modelNameOrUrl);
    void fetchInfo(QString host, QString modelNameOrUrl);
    void handleInfoResult(WebcamInfo webcamInfo);
    void openDirectory(QString directory);
    void startDownload(QVariantMap webcamInfo, QString directory);
    void stopDownload(QString host, QString modelName);
    void stopAllDownloads();
    QString getFriendlyName(QString host);

private:
    QList<WebcamHost*> webcamHosts;
    WebcamHost* current();
    WebcamHost* getHost(QString hostname);
    QString currentHostName;
    QThread workerThread;
    Ffmpeg* ffmpeg = new Ffmpeg(this);
};

#endif // WEBCAMREGISTRY_H
