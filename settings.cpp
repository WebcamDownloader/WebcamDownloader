#include "settings.h"

Settings::Settings(QObject *parent)
    : Settings(true, parent)
{
}

Settings::Settings(bool readOnly, QObject *parent)
    : QObject(parent),
      settings(QCoreApplication::applicationDirPath() + "/options.ini", QSettings::IniFormat, this),
      isReadOnly(readOnly)
{
}

QVariantList Settings::getModels(QString host)
{
    QVariantList result;

    settings.beginGroup("models_" + host);
    auto modelNames = settings.childGroups();
    QListIterator<QString> modelNamesIterator(modelNames);
    while (modelNamesIterator.hasNext()) {
        auto modelName = modelNamesIterator.next();
        settings.beginGroup(modelName);

        ModelSetting model(settings.value("modelName").toString(), settings.value("autoDownload").toBool());
        result.append(model.toMap());

        settings.endGroup();
    }
    settings.endGroup();

    return result;
}

QVariantMap Settings::getModels()
{
    QVariantMap result;

    auto types = webcamRegistry.getTypes();
    QMapIterator<QString, QVariant> iterator(types);
    while (iterator.hasNext()) {
        auto value = iterator.next();
        result.insert(value.key(), getModels(value.key()));
    }

    return result;
}

void Settings::setModelData(QString host, QString modelName, bool autoDownload)
{
    if (isReadOnly) {
        return;
    }
    settings.beginGroup("models_" + host);
    settings.beginGroup(modelName);
    settings.setValue("modelName", modelName);
    settings.setValue("autoDownload", autoDownload);
    settings.endGroup();
    settings.endGroup();

    emit modelsUpdated();
}

void Settings::setModelData(QString host, QString modelName)
{
    if (isReadOnly) {
        return;
    }
    auto data = getModelData(host, modelName);
    setModelData(host, modelName, data.value("autoDownload").toBool());
}

QVariantMap Settings::getModelData(QString host, QString modelName)
{
    settings.beginGroup("models_" + host);
    settings.beginGroup(modelName);
    auto result = ModelSetting(
                settings.value("modelName", "").toString(),
                settings.value("autoDownload", false).toBool()
            )
            .toMap();
    settings.endGroup();
    settings.endGroup();

    return result;
}

void Settings::deleteModel(QString host, QString modelName)
{
    if (isReadOnly) {
        return;
    }
    settings.beginGroup("models_" + host);
    settings.remove(modelName);
    settings.endGroup();

    emit modelsUpdated();
}

int Settings::getWindowWidth()
{
    settings.beginGroup("app_settings");
    int width = settings.value("window_width", 640).toInt();
    settings.endGroup();
    return width;
}

int Settings::getWindowHeight()
{
    settings.beginGroup("app_settings");
    int width = settings.value("window_height", 480).toInt();
    settings.endGroup();
    return width;
}

void Settings::setWindowWidth(int width)
{
    if (isReadOnly) {
        return;
    }
    settings.beginGroup("app_settings");
    settings.setValue("window_width", width);
    settings.endGroup();
}

void Settings::setWindowHeight(int height)
{
    if (isReadOnly) {
        return;
    }
    settings.beginGroup("app_settings");
    settings.setValue("window_height", height);
    settings.endGroup();
}

bool Settings::closeToTray()
{
    settings.beginGroup("app_settings");
    bool enabled = settings.value("minimize_to_tray", false).toBool();
    settings.endGroup();
    return enabled;
}

void Settings::setCloseToTray(bool minimize)
{
    if (isReadOnly) {
        return;
    }
    settings.beginGroup("app_settings");
    settings.setValue("minimize_to_tray", minimize);
    settings.endGroup();
}

QString Settings::downloadDirectory()
{
    settings.beginGroup("app_settings");
    QString directory = settings.value("directory", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)).toString();
    settings.endGroup();
    return directory;
}

void Settings::setDownloadDirectory(QString directory)
{
    if (isReadOnly) {
        return;
    }
    if (directory.startsWith("file:///")) {
        directory.remove(0, QString("file:///").count());
    }
    if (directory != downloadDirectory()) {
        settings.beginGroup("app_settings");
        settings.setValue("directory", directory);
        settings.endGroup();
        emit downloadDirectoryChanged();
    }
}

bool Settings::checkForNewVersions()
{
    settings.beginGroup("app_settings");
    auto enabled = settings.value("check_for_new_versions", true).toBool();
    settings.endGroup();
    return enabled;
}

void Settings::setCheckForNewVersions(bool check)
{
    if (isReadOnly) {
        return;
    }
    if (check != checkForNewVersions()) {
        settings.beginGroup("app_settings");
        settings.setValue("check_for_new_versions", check);
        settings.endGroup();
        emit checkForNewVersionsChanged();
    }
}

bool Settings::autoDownloadsEnabled()
{
    settings.beginGroup("app_settings");
    bool enabled = settings.value("auto_downloads_enabled", false).toBool();
    settings.endGroup();
    return enabled;
}

void Settings::setAutoDownloadsEnabled(bool enabled)
{
    if (isReadOnly) {
        return;
    }
    if (enabled != autoDownloadsEnabled()) {
        settings.beginGroup("app_settings");
        settings.setValue("auto_downloads_enabled", enabled);
        settings.endGroup();
        emit autoDownloadsEnabledChanged();
    }
}

