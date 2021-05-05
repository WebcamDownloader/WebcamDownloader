#ifndef ADDMODELCOMMAND_H
#define ADDMODELCOMMAND_H

#include "command.h"
#include "../webcamregistry.h"
#include "../settings.h"

class AddModelCommand : public Command
{
    Q_OBJECT
public:
    explicit AddModelCommand(QObject *parent = nullptr);
    QString name() override;
    void run() override;
    QString description() override;
    QString help() override;

private:
    bool isValidHost(QString host);
    WebcamRegistry registry;
    Settings settings;
    QString usageString = "Usage: WebcamDownloader add host {modelName | modelUrl} [--autodownload]";
};

#endif // ADDMODELCOMMAND_H
