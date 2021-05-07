#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include <QTextStream>
#include <cmath>

#include "command.h"

class HelpCommand : public Command
{
    Q_OBJECT
public:
    explicit HelpCommand(QObject *parent, QList<Command*> *commands);
    bool isDefault() override;
    QString name() override;
    QString description() override;
    QString help() override;
    void run() override;

private:
    QString getDescription(QString commandName);
    QList<Command*>* commands;
};

#endif // HELPCOMMAND_H
