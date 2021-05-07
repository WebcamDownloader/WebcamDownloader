#include "helpcommand.h"

HelpCommand::HelpCommand(QObject *parent, QList<Command*> *commands)
    : Command(parent), commands(commands)
{

}

bool HelpCommand::isDefault()
{
    return true;
}

QString HelpCommand::name()
{
    return "help";
}

QString HelpCommand::description()
{
    return "Display this help";
}

QString HelpCommand::help()
{
    return "Wow, running a help command on help command? That's like helpception.";
}

void HelpCommand::run()
{
    QTextStream out(stdout);
    QTextStream err(stderr);

    int exitCode = arguments->at(0) == name() ? 0 : 1;
    arguments->removeAt(0);

    if (arguments->count() == 0) {
        err << "Usage: WebcamDownloader [command] [arguments]" << "\n";
        err << "List of commands:" << "\n";
        QListIterator<Command*> iterator(*commands);
        while (iterator.hasNext()) {
            auto command = iterator.next();
            if (command->isInternal()) {
                continue;
            }
            int tabCount = 3 - ceil(command->name().length() / 6.0);
            QString tabs = QString("\t").repeated(tabCount);

            err << " " << command->name() << tabs << command->description() << "\n";
        }
        err << "You can also use help [command] to display detailed information about the command" << "\n";
    } else {
        bool found = false;
        QListIterator<Command*> iterator(*commands);
        while (iterator.hasNext()) {
            auto command = iterator.next();
            if (command->name() == arguments->at(0)) {
                err << command->help() << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            err << "Command '" << arguments->at(0) << "' not found" << "\n";
            exitCode = 2;
        }
    }
    emit commandFinished(exitCode);
}
