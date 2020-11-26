#ifndef WEBCAMINFO_H
#define WEBCAMINFO_H

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class WebcamInfo
{
public:
    explicit WebcamInfo(QString host, QString modelName, bool isOnline, QUrl streamUrl, bool error);
    WebcamInfo();
    WebcamInfo(QVariantMap map);

    QVariantMap toMap();
    bool isSuccessful();
    QString modelName();
    QString host();
    QUrl streamUrl();

    bool operator>(const WebcamInfo& right) const;
    bool operator<(const WebcamInfo& right) const;

private:
    QString mHost;
    QString mModelName;
    bool mIsOnline;
    QUrl mStreamUrl;
    bool mError;
};

#endif // WEBCAMINFO_H
