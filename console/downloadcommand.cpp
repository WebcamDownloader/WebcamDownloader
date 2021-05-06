#include "downloadcommand.h"

#include <QDebug>

DownloadCommand::DownloadCommand(QObject *parent): Command(parent), settings(this)
{
}

QString DownloadCommand::name()
{
    return "start";
}

void DownloadCommand::run()
{
    QTextStream err(stderr);

    arguments->removeAt(0);

    Ffmpeg *ffmpeg = new Ffmpeg(this);
    QEventLoop mainLoop;
    WebcamRegistry webcamRegistry;

    QStringList filter = *arguments;
    QStringList models;

    QMapIterator<QString, QVariant> modelsMapIterator(settings.getModels());
    while (modelsMapIterator.hasNext()) {
        modelsMapIterator.next();
        auto host = modelsMapIterator.key();
        QListIterator<QVariant> modelsIterator(modelsMapIterator.value().toList());
        while (modelsIterator.hasNext()) {
            auto model = modelsIterator.next().toMap();
            auto modelName = model.value("modelName").toString();
            if (model.value("autoDownload").toBool() && (filter.size() == 0 || filter.contains(modelName))) {
                models << host << modelName;
            }
        }
    }

    connect(&webcamRegistry, &WebcamRegistry::results, &mainLoop, [&err, ffmpeg, this](QVariantMap result) {
        WebcamInfo webcamInfo(
            result.value("host").toString(),
            result.value("modelName").toString(),
            result.value("isOnline").toBool(),
            result.value("streamUrl").toString(),
            false
        );
        if (webcamInfo.online()) {
            qDebug() << QString("Found online model '%1' of host '%2'").arg(webcamInfo.modelName()).arg(webcamInfo.host()) << "\n";
            ffmpeg->startDownload(webcamInfo, settings.downloadDirectory());
        }
    });
    connect(ffmpeg, &Ffmpeg::downloadStarted, &mainLoop, [&err](QString host, QString modelName) {
        qDebug() << QString("Started downloading of model '%1' from host '%2'").arg(modelName).arg(host) << "\n";
    });
    connect(ffmpeg, &Ffmpeg::downloadEnded, &mainLoop, [&err](QString host, QString modelName) {
        qDebug() << QString("Stopped downloading of model '%1' from host '%2'").arg(modelName).arg(host) << "\n";
    });
    connect(this, &DownloadCommand::validModelsFound, &mainLoop, [&err](int count) {
        qDebug() << QString("Found %1 models to download").arg(count) << "\n";
    });
    connect(this, &DownloadCommand::onlineModelsFound, &mainLoop, [&err](int count) {
        qDebug() << QString("%1 of those models are online").arg(count) << "\n";
    });

    for (auto i = 0; i < models.size(); i += 2) {
        auto host = models.at(i);
        auto name = models.at(i + 1);

        webcamRegistry.fetchInfo(host, name);
    }

    mainLoop.exec();
}

QString DownloadCommand::description()
{
    return "Starts downloading the webcam streams";
}

QString DownloadCommand::help()
{
    return QString(
        "Starts downloading the webcam streams." "\n"
        "All arguments are the names of saved model names." "\n"
        "If you use the command without arguments, all models set to autodownload will be downloaded instead." "\n"
        "To cancel the download, send a SIGINT to this app." "\n"
        "\n"
        "Usage:" "\n"
        "\n"
        "WebcamDownloader start model_name_1 model_name_2" "\n"
        "(will start downloading models named model_name_1 and model_name_2)" "\n"
        "\n"
        "WebcamDownloader start" "\n"
        "(will start downloading all models that are set to autodownload)" "\n"
    );
}
