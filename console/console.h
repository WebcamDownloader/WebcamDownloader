#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QCoreApplication>

#include "command.h"

#include "helpcommand.h"
#include "listhostscommand.h"
#include "listmodelscommand.h"
#include "addmodelcommand.h"
#include "removemodelcommand.h"
#include "downloadcommand.h"
#include "settingscommand.h"

class Console : public QObject
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);
    Command* findCommand(QString name);
    Command* findCommand(QStringList arguments);

private:
    QList<Command*> commands;
};

#endif // CONSOLE_H
