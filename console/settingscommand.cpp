#include "settingscommand.h"

SettingsCommand::SettingsCommand(QObject *parent) : Command(parent), settings(false, this)
{
}

QString SettingsCommand::name()
{
    return "settings";
}

QString SettingsCommand::description()
{
    return "Set various app settings (download directory etc.)";
}

QString SettingsCommand::help()
{
    auto help = QString(
        "Set various app settings." "\n"
        "\n"
        "Usage:" "\n"
        "WebcamDownloader settings <setting-name> <setting-value>" "\n"
        "Set setting <setting-name> to <setting-value>" "\n" "\n"
        "WebcamDownloader setting <setting-name>" "\n"
        "Get the current value of setting <setting-name>" "\n" "\n"
        "Example: WebcamDownloader settings download-dir /path/to/download/dir" "\n"
        "\n"
        "List of available settings:" "\n"
    );

    QMapIterator<QString, QString> iterator(availableSettings());
    while (iterator.hasNext()) {
        iterator.next();
        auto setting = iterator.key();
        auto description = iterator.value();

        int tabCount = 5 - ceil(setting.length() / 5.0);
        QString tabs = QString("\t").repeated(tabCount);

        help += setting + tabs + description + "\n";
    }

    return help;
}

void SettingsCommand::run()
{
    QTextStream err(stderr);
    QTextStream out(stdout);

    if (arguments->length() == 1) {
        err << "Missing arguments. Usage:" << "\n"
            << "WebcamDownloader settings <setting-name>" << "\n"
            << "WebcamDownloader settings <setting-name> <setting-value>" << "\n"
            << "For list of available settings run: WebcamDownloader help settings" << "\n";
        emit commandFinished(1);
        return;
    }

    auto settingName = arguments->at(1);
    if (!availableSettings().keys().contains(settingName)) {
        err << "Invalid setting '" << settingName << "'." << "\n"
            << "For list of available options run: WebcamDownloader help settings" << "\n";
        emit commandFinished(2);
        return;
    }

    if (arguments->length() == 2) {
        out << getSettingValue(settingName) << "\n";
        emit commandFinished(0);
        return;
    }

    setSettingValue(settingName, arguments->at(2));
    emit commandFinished(0);
}

QMap<QString, QString> SettingsCommand::availableSettings()
{
    QMap<QString, QString> settings;

    settings.insert("download-dir", "The target directory to download webcam shows to");
#ifndef NO_GUI
    settings.insert("auto-downloads", "Set to true or false to enable or disable automatic downloads (affects only GUI)");
    settings.insert("new-version-check", "Set to true or false to enable or disable the app checking for new versions (affects only GUI)");
#endif
    return settings;
}

QString SettingsCommand::getSettingValue(QString settingName)
{
    if (settingName == "download-dir") {
        return settings.downloadDirectory();
    }
    if (settingName == "auto-downloads") {
        return settings.autoDownloadsEnabled() ? "true" : "false";
    }
    if (settingName == "new-version-check") {
        return settings.checkForNewVersions() ? "true" : "false";
    }

    return "";
}

void SettingsCommand::setSettingValue(QString settingName, QString settingValue)
{
    if (settingName == "download-dir") {
        settings.setDownloadDirectory(settingValue);
    } else if (settingName == "auto-downloads") {
        settings.setAutoDownloadsEnabled(settingValue == "true" || settingValue == "yes" || settingValue == "y");
    } else if (settingName == "new-version-check") {
        settings.setCheckForNewVersions(settingValue == "true" || settingValue == "yes" || settingValue == "y");
    }
}
