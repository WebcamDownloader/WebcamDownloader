#ifndef USERAGENTGENERATOR_H
#define USERAGENTGENERATOR_H

#include <QString>
#include <QStringList>
#include <QRandomGenerator>

class UserAgentGenerator
{
public:
    UserAgentGenerator();
    QString getRandomUserAgent();
private:
    QStringList userAgents;
};

#endif // USERAGENTGENERATOR_H
