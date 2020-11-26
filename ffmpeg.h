#ifndef FFMPEG_H
#define FFMPEG_H

#include <QObject>
#include <QUrl>
#include <QStandardPaths>
#include <QProcess>
#include <QCoreApplication>
#include <QDateTime>

#include "webcaminfo.h"
#include "useragentgenerator.h"

class Ffmpeg : public QObject
{
    Q_OBJECT
public:
    explicit Ffmpeg(QObject *parent = nullptr);
    ~Ffmpeg();
    void startDownload(WebcamInfo webcamInfo, QString directory);
    void stopAllDownloads();
    void stopDownload(WebcamInfo info);
    void stopDownload(QString host, QString modelName);

signals:
    void downloadStarted(QString host, QString modelName);
    void downloadEnded(QString host, QString modelName);

private:
    bool hasDownload(WebcamInfo webcamInfo);
    bool hasDownload(QString host, QString modelName);
    UserAgentGenerator userAgentGenerator;
    QMap<WebcamInfo, QProcess*> processes;
#ifdef Q_OS_WIN
    const QString binary = QCoreApplication::applicationDirPath() + "/ffmpeg.exe";
#else
    const QString binary = "ffmpeg";
#endif
};

#endif // FFMPEG_H
