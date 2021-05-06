#ifndef DOWNLOADCOMMAND_H
#define DOWNLOADCOMMAND_H

#include <QMapIterator>
#include <QListIterator>

#include "command.h"
#include "../settings.h"
#include "../webcamregistry.h"
#include "../ffmpeg.h"

class DownloadCommand : public Command
{
    Q_OBJECT
public:
    explicit DownloadCommand(QObject *parent = nullptr);
    QString name() override;
    void run() override;
    QString description() override;
    QString help() override;
    virtual bool isInternal() override;

signals:
    void validModelsFound(int count);
    void onlineModelsFound(int count);

private:
    Settings settings;
};

#endif // DOWNLOADCOMMAND_H
