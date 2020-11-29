#include "listmodelscommand.h"

ListModelsCommand::ListModelsCommand(QObject *parent) : Command(parent)
{
    allowedFormats = QStringList() << "text" << "csv" << "json";
}

QString ListModelsCommand::description()
{
    return "Lists all models that you added to list";
}

QString ListModelsCommand::help()
{

    return QString(
                "Lists all models you've added separated by tabulators (by default) in this format:" "\n"
                "<model name>\t<host>\t<auto-download>" "\n"
                "Where <auto-download> is either the string true or false "
                "(for text and csv mode, in json it's actual true/false value)"
                "\n" "\n"

                "Usage: WebcamDownloader models [--format=]" "\n"
                "Supported formats: %1" "\n"
           ).arg(allowedFormats.join(", "));
}

QString ListModelsCommand::name()
{
    return "models";
}

int ListModelsCommand::run(QStringList arguments)
{
    QTextStream err(stderr);
    QTextStream out(stdout);

    auto format = findFormat(arguments);

    if (!allowedFormats.contains(format)) {
        err << "Unsupported format: " << format << "\n"
            << "Valid values are: " << allowedFormats.join(", ") << "\n";
        return 1;
    }

    auto writer = getWriter(format);
    assert(writer != nullptr);
    auto modelsMap = settings.getModels();
    QMapIterator<QString, QVariant> modelsMapIterator(modelsMap);
    while (modelsMapIterator.hasNext()) {
        modelsMapIterator.next();
        auto host = modelsMapIterator.key();
        auto models = modelsMapIterator.value().toList();
        QListIterator<QVariant> modelsIterator(models);
        while (modelsIterator.hasNext()) {
            auto model = modelsIterator.next().toMap();
            writer->addModel(host, model.value("modelName").toString(), model.value("autoDownload").toBool());
        }
    }
    auto result = writer->getOutput();
    delete writer;

    out << result;

    return 0;
}

QString ListModelsCommand::findFormat(QStringList arguments)
{
    QString format = "text";
    if (int index = arguments.indexOf("--format"); index > -1 && arguments.size() > index) {
        format = arguments.at(index + 1);
    }

    QListIterator<QString> iterator(arguments);
    while (iterator.hasNext()) {
        auto argument = iterator.next();
        if (argument.indexOf("--format=") == 0) {
            format = argument.mid(QString("--format").size() + 1);
            break;
        }
    }

    return format;
}

ListModelsCommand::OutputWriter* ListModelsCommand::getWriter(QString format)
{
    if (format == "text") {
        return new TextOutputWriter();
    } else if (format == "json") {
        return new JsonOutputWriter();
    } else if (format == "csv") {
        return new CsvOutputWriter();
    }

    return nullptr;
}

ListModelsCommand::OutputWriter::~OutputWriter()
{
}

void ListModelsCommand::OutputWriter::addModel(QString host, QString modelName, bool autoDownload)
{
    QMap<QString, QVariant> map;
    map.insert("host", host);
    map.insert("modelName", modelName);
    map.insert("autoDownload", autoDownload);
    outputLines.append(map);
}

QListIterator<QMap<QString, QVariant>> ListModelsCommand::OutputWriter::outputLinesIterator()
{
    return QListIterator<QMap<QString, QVariant>>(outputLines);
}

QString ListModelsCommand::TextOutputWriter::getOutput()
{
    QString result;

    auto iterator = outputLinesIterator();
    while (iterator.hasNext()) {
        auto row = iterator.next();
        result += row.value("modelName").toString()
                + "\t"
                + row.value("host").toString()
                + "\t"
                + (row.value("autoDownload").toBool() ? "true" : "false")
                + "\n";
    }

    return result;
}

QString ListModelsCommand::JsonOutputWriter::getOutput()
{
    QJsonArray result;
    auto iterator = outputLinesIterator();
    while (iterator.hasNext()) {
        auto row = iterator.next();
        QJsonObject object;
        object.insert("modelName", row.value("modelName").toString());
        object.insert("host", row.value("host").toString());
        object.insert("autoDownload", row.value("autoDownload").toBool());
        result.append(object);
    }
    return QJsonDocument(result).toJson();
}

QString ListModelsCommand::CsvOutputWriter::getOutput()
{
    QString result;
    auto iterator = outputLinesIterator();
    while (iterator.hasNext()) {
        auto row = iterator.next();
        result += "\"" + row.value("modelName").toString() + "\"" + ","
                + row.value("host").toString() + ","
                + (row.value("autoDownload").toBool() ? "true" : "false") + "\n";
    }
    return result;
}
