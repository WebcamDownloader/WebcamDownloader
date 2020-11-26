#ifndef MODELSETTING_H
#define MODELSETTING_H

#include <QString>
#include <QVariant>

class ModelSetting
{
public:
    explicit ModelSetting(QString name, bool autoDownload);
    ModelSetting(QVariantMap map);
    QVariantMap toMap();
private:
    QString name;
    bool autoDownload;
};

#endif // MODELSETTING_H
