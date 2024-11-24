#include "ffmpeg.h"
#include <QDebug>

Ffmpeg::Ffmpeg(QObject *parent)
    : QObject(parent)
{
}

Ffmpeg::~Ffmpeg()
{
    stopAllDownloads();
}

void Ffmpeg::startDownload(WebcamInfo webcamInfo, QString directory)
{
    if (hasDownload(webcamInfo)) {
        return;
    }

#ifdef Q_OS_LINUX
    if (!directory.startsWith("/")) {
        directory = "/" + directory;
    }
#endif

    QString host = webcamInfo.host();
    QString modelName = webcamInfo.modelName();

    QDateTime datetime = QDateTime::currentDateTime();
    QString outPath = directory
            + "/" + modelName
            + "-" + datetime.toString("yyyy_MM_dd-hh_mm_ss")
            + ".ts";

    QString ffmpegPath = outPath;
#ifdef Q_OS_WIN
    ffmpegPath = ffmpegPath.replace("/", "\\");
#endif
    QProcess *process = new QProcess();
    process->setProgram(binary);
    process->setArguments(
        QStringList()
                << "-f" << "hls"
                << "-headers" << "Referer: https://stripchat.com/" + modelName
                << "-user_agent" << userAgentGenerator.getRandomUserAgent()
                << "-i" << webcamInfo.streamUrl().toString()
                << "-c" << "copy"
                << ffmpegPath
    );

    connect(process, &QProcess::started, this, [this, host, modelName]() {
        emit downloadStarted(host, modelName);
    });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this, host, modelName]() {
        emit downloadEnded(host, modelName);
    });
    connect(process, &QProcess::errorOccurred, this, [process](QProcess::ProcessError error) {
        qDebug() << error;
        qDebug() << process->errorString();
        qDebug() << process->arguments();
    });
    process->start();
    processes.insert(webcamInfo, process);
}

void Ffmpeg::stopAllDownloads()
{
    QMapIterator<WebcamInfo, QProcess*> iterator(processes);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto key = item.key();

        stopDownload(key);
    }

}

void Ffmpeg::stopDownload(WebcamInfo info)
{
    stopDownload(info.host(), info.modelName());
}

void Ffmpeg::stopDownload(QString host, QString modelName)
{
    if (!hasDownload(host, modelName)) {
        return;
    }

    QMapIterator<WebcamInfo, QProcess*> iterator(processes);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto info = item.key();
        if (info.modelName() == modelName && info.host() == host) {
            auto process = item.value();
            if (process != nullptr && process->state() == QProcess::Running) {
#ifdef Q_OS_WIN
                process->kill();
#else
                process->terminate();
#endif
                delete process;
                processes.remove(info);
            }
        }
    }
}

bool Ffmpeg::hasDownload(WebcamInfo webcamInfo)
{
    return hasDownload(webcamInfo.host(), webcamInfo.modelName());
}

bool Ffmpeg::hasDownload(QString host, QString modelName)
{
    QMapIterator<WebcamInfo, QProcess*> iterator(processes);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto info = item.key();
        if (info.modelName() == modelName && info.host() == host && item.value()->state() == QProcess::Running) {
            return true;
        }
    }

    return false;
}

