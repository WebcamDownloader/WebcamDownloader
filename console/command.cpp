#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

bool Command::isDefault()
{
    return false;
}

void Command::setArguments(QStringList &arguments)
{
    this->arguments = &arguments;
}

bool Command::isInternal()
{
    return false;
}

