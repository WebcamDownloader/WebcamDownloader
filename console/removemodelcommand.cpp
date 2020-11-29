#include "removemodelcommand.h"

RemoveModelCommand::RemoveModelCommand(QObject *parent) : Command(parent), settings(false, this)
{
}

QString RemoveModelCommand::name()
{
    return "remove";
}

int RemoveModelCommand::run(QStringList arguments)
{
    QTextStream err(stderr);

    if (arguments.length() < 2) {
        err << "Wrong arguments count" << "\n" << usage << "\n";
        return 1;
    }
    arguments.removeAt(0);

    bool silentFail = false;
    if (auto silentFailIndex = arguments.indexOf("--silentfail"); silentFailIndex > -1) {
        silentFail = true;
        arguments.removeAt(silentFailIndex);
    }
    auto modelsToDelete = findModelsToDelete(arguments);

    if (modelsToDelete.size() == 0 && silentFail) {
        return 0;
    } else if (modelsToDelete.size() == 0) {
        err << "Model not found in database" << "\n";
        return 2;
    }

    QMapIterator<QString, QString> iterator(modelsToDelete);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto host = item.key();
        auto model = item.value();
        settings.deleteModel(host, model);
    }

    return 0;
}

QString RemoveModelCommand::description()
{
    return "Removes a model from database";
}

QString RemoveModelCommand::help()
{
    return
            usage + "\n\n"
            "If no host is specified in an argument and there is more than one model with the same name "
            "(e.g. from different hosts), all of them will be deleted." "\n"
            "Returns exit code 2 if the model was not found unless flag --silentfail is present" "\n"
            "Prints no output in case of success." "\n"
            ;
}

QMap<QString, QString> RemoveModelCommand::findModelsToDelete(QStringList arguments)
{
    QMap<QString, QString> result;

    auto modelsMap = settings.getModels();
    if (arguments.count() == 2) {
        if (
            modelsMap.contains(arguments.at(0))
        ) {
            auto models = modelsMap.value(arguments.at(0)).toList();
            QListIterator<QVariant> modelsIterator(models);
            while (modelsIterator.hasNext()) {
                auto model = modelsIterator.next().toMap();
                if (auto modelName = model.value("modelName").toString(); modelName == arguments.at(1)) {
                    result.insert(arguments.at(0), modelName);
                }
            }
        }
    } else {
        QMapIterator<QString, QVariant> modelsMapIterator(modelsMap);
        while (modelsMapIterator.hasNext()) {
            modelsMapIterator.next();
            auto host = modelsMapIterator.key();
            auto models = modelsMapIterator.value().toList();
            QListIterator<QVariant> modelsIterator(models);
            while (modelsIterator.hasNext()) {
                auto model = modelsIterator.next().toMap();
                if (auto modelName = model.value("modelName").toString(); modelName == arguments.at(0)) {
                    result.insert(host, modelName);
                }
            }
        }
    }

    return result;
}
