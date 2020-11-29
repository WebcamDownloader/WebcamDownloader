#ifndef REMOVEMODELCOMMAND_H
#define REMOVEMODELCOMMAND_H

#include <QMap>

#include "command.h"
#include "../settings.h"

class RemoveModelCommand : public Command
{
    Q_OBJECT
public:
    explicit RemoveModelCommand(QObject *parent = nullptr);
    QString name() override;
    int run(QStringList arguments) override;
    QString description() override;
    QString help() override;

private:
    QString usage = "Usage: WebcamDownloder remove [host] model [--silentfail]";
    Settings settings;
    QMap<QString, QString> findModelsToDelete(QStringList arguments);
};

#endif // REMOVEMODELCOMMAND_H
