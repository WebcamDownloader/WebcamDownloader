#include "console.h"

Console::Console(QObject *parent) : QObject(parent)
{
    commands.append(new ListHostsCommand(this));
    commands.append(new ListModelsCommand(this));
    commands.append(new AddModelCommand(this));
    commands.append(new RemoveModelCommand(this));
    commands.append(new DownloadCommand(this));
    commands.append(new SettingsCommand(this));
    commands.append(new HelpCommand(this, &commands));
}

Command *Console::findCommand(QString name)
{
    QListIterator<Command*> iterator(commands);
    Command* defaultCommand = nullptr;

    while (iterator.hasNext()) {
        auto command = iterator.next();
        if (command->isDefault()) {
            defaultCommand = command;
        }
        if (command->name() == name) {
            return command;
        }
    }

    return defaultCommand;
}

Command *Console::findCommand(QStringList arguments)
{
    return findCommand(arguments.at(1));
}
