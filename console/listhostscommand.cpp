#include "listhostscommand.h"

ListHostsCommand::ListHostsCommand(QObject *parent) : Command(parent)
{
}

QString ListHostsCommand::description()
{
    return "Prints list of available hosts";
}

QString ListHostsCommand::help()
{
    return "Prints list of all hosts available to use in other commands, one per line";
}

QString ListHostsCommand::name()
{
    return "hosts";
}

int ListHostsCommand::run(QStringList arguments)
{
    Q_UNUSED(arguments);
    QTextStream out(stdout);
    QMapIterator<QString, QVariant> iterator(registry->getTypes());
    while (iterator.hasNext()) {
        out << iterator.next().key() << "\n";
    }
    return 0;
}
