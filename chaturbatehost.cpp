#include "chaturbatehost.h"

ChaturbateHost::ChaturbateHost(QObject *parent) : WebcamHost(parent)
{

}

QString ChaturbateHost::getName()
{
    return "Chaturbate";
}

QString ChaturbateHost::getCodeName()
{
    return "chaturbate";
}

WebcamInfo ChaturbateHost::getModelInfo(QString urlOrName)
{
    Q_UNUSED(urlOrName);
    return WebcamInfo();
}
