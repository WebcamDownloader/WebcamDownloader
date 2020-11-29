#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

bool Command::isDefault()
{
    return false;
}
