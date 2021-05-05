#ifndef LISTHOSTSCOMMAND_H
#define LISTHOSTSCOMMAND_H

#include "command.h"
#include "../webcamregistry.h"

class ListHostsCommand : public Command
{
    Q_OBJECT
public:
    explicit ListHostsCommand(QObject *parent = nullptr);
    QString description() override;
    QString help() override;
    QString name() override;
    void run() override;
private:
    WebcamRegistry *registry = new WebcamRegistry(this);
};

#endif // LISTHOSTSCOMMAND_H
