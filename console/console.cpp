#include "console.h"

Console::Console(QObject *parent) : QObject(parent)
{
    commands.append(new ListHostsCommand(this));
    commands.append(new ListModelsCommand(this));
    commands.append(new AddModelCommand(this));
    commands.append(new RemoveModelCommand(this));
    commands.append(new HelpCommand(this, &commands));
}

int Console::handler(QCoreApplication *app)
{
    auto arguments = app->arguments();
    return handler(app->arguments());
}

int Console::handler(QStringList arguments)
{
    auto command = findCommand(arguments.at(1));
    arguments.removeAt(0);
    return command->run(arguments);
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
