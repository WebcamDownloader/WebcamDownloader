#include "addmodelcommand.h"

AddModelCommand::AddModelCommand(QObject *parent) : Command(parent), settings(false, this)
{
}

QString AddModelCommand::name()
{
    return "add";
}

void AddModelCommand::run()
{
    QTextStream err(stderr);

    if (arguments->length() < 3) {
        err << "Wrong arguments count!" << "\n"
            << usageString << "\n";
        emit commandFinished(1);
        return;
    }

    auto hostName = arguments->at(1);
    auto modelName = arguments->at(2);

    if (!isValidHost(hostName)) {
        err << "Invalid host: " << hostName << "\n";
        emit commandFinished(2);
        return;
    }

    auto host = registry.getHost(hostName);
    auto info = host->getModelInfo(modelName);

    if (info.error()) {
        err << "The model was not found" << "\n";
        emit commandFinished(3);
    }

    settings.setModelData(info.host(), info.modelName(), arguments->contains("--autodownload"));
    emit commandFinished();
}

QString AddModelCommand::description()
{
    return "Adds a new model to database";
}

QString AddModelCommand::help()
{
    return
            usageString + "\n\n"
            "Where host is one of the hosts returned by 'WebcamDownloader hosts' command." "\n"
            "If the --autodownload flag is present the model will be added to the autodownload list." "\n"
            "Doesn't print any output in case of success.";
}

bool AddModelCommand::isValidHost(QString host)
{
    return registry.getTypes().keys().contains(host);
}
