#include "webcaminfo.h"


WebcamInfo::WebcamInfo(
        QString host,
        QString modelName,
        bool isOnline,
        QUrl streamUrl,
        bool error
) : mHost(host),
    mModelName(modelName),
    mIsOnline(isOnline),
    mStreamUrl(streamUrl),
    mError(error)
{
}

WebcamInfo::WebcamInfo()
    : WebcamInfo("", "", false, QUrl(), true)
{
}

WebcamInfo::WebcamInfo(QString host, QString modelName)
    : WebcamInfo(host, modelName, false, QUrl(), true)
{
}

WebcamInfo::WebcamInfo(QVariantMap map)
    : WebcamInfo(
          map.value("host").toString(),
          map.value("modelName").toString(),
          map.value("isOnline").toBool(),
          map.value("streamUrl").toUrl(),
          false
    )
{
}

QVariantMap WebcamInfo::toMap()
{
    QVariantMap map;

    map.insert("host", mHost);
    map.insert("modelName", mModelName);
    map.insert("isOnline", mIsOnline);
    map.insert("streamUrl", mStreamUrl);

    return map;
}

bool WebcamInfo::isSuccessful()
{
    return !mError;
}

QString WebcamInfo::modelName()
{
    return mModelName;
}

QString WebcamInfo::host()
{
    return mHost;
}

QUrl WebcamInfo::streamUrl()
{
    return mStreamUrl;
}

bool WebcamInfo::error()
{
    return mError;
}

bool WebcamInfo::operator>(const WebcamInfo &right) const
{
    return mModelName > right.mModelName;
}

bool WebcamInfo::operator<(const WebcamInfo &right) const
{
    return mModelName < right.mModelName;
}

