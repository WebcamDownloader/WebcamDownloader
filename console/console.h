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

class Console : public QObject
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);
    int handler(QCoreApplication *app);
    int handler(QStringList arguments);

private:
    Command* findCommand(QString name);
    QList<Command*> commands;
};

#endif // CONSOLE_H
