#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QStandardPaths>
#include <QSettings>
#include <QCoreApplication>

#include "webcamregistry.h"
#include "webcaminfo.h"
#include "modelsetting.h"

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool autoDownloadsEnabled READ autoDownloadsEnabled WRITE setAutoDownloadsEnabled NOTIFY autoDownloadsEnabledChanged)
public:
    explicit Settings(QObject *parent = nullptr);

    bool autoDownloadsEnabled();
    void setAutoDownloadsEnabled(bool enabled);

signals:
    void modelsUpdated();
    void autoDownloadsEnabledChanged();

public slots:
    QVariantList getModels(QString host);
    QVariantMap getModels();
    void setModelData(QString host, QString modelName, bool autoDownload);
    void setModelData(QString host, QString modelName);
    QVariantMap getModelData(QString host, QString modelName);
    void deleteModel(QString host, QString modelName);

    int getWindowWidth();
    int getWindowHeight();
    void setWindowWidth(int width);
    void setWindowHeight(int height);

    bool closeToTray();
    void setCloseToTray(bool minimize);

private:
    QSettings settings;
    WebcamRegistry webcamRegistry;
};

#endif // SETTINGS_H
