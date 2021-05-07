#ifndef SETTINGSCOMMAND_H
#define SETTINGSCOMMAND_H

#include <QMap>
#include <QMapIterator>
#include <cmath>

#include "command.h"
#include "../settings.h"

class SettingsCommand : public Command
{
    Q_OBJECT
public:
    explicit SettingsCommand(QObject *parent = nullptr);
    QString name() override;
    QString description() override;
    QString help() override;
    void run() override;

private:
    QMap<QString, QString> availableSettings();
    QString getSettingValue(QString settingName);
    void setSettingValue(QString settingName, QString settingValue);

    Settings settings;
};

#endif // SETTINGSCOMMAND_H
