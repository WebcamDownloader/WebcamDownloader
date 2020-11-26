#include "modelsetting.h"

ModelSetting::ModelSetting(QString name, bool autoDownload)
{
    this->name = name;
    this->autoDownload = autoDownload;
}

ModelSetting::ModelSetting(QVariantMap map)
    : name(map.value("modelName").toString()), autoDownload(map.value("autoDownload").toBool())
{
}

QVariantMap ModelSetting::toMap()
{
    QVariantMap map;
    map.insert("modelName", name);
    map.insert("autoDownload", autoDownload);
    return map;
}

