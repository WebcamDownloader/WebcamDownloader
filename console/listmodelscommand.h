#ifndef LISTMODELSCOMMAND_H
#define LISTMODELSCOMMAND_H

#define classes

#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "command.h"
#include "../settings.h"

class ListModelsCommand : public Command
{
    Q_OBJECT
public:
    explicit ListModelsCommand(QObject *parent = nullptr);
    QString description() override;
    QString help() override;
    QString name() override;
    int run(QStringList arguments) override;

private classes:
    class OutputWriter {
    public:
        virtual ~OutputWriter();
        void addModel(QString host, QString modelName, bool autoDownload);
        virtual QString getOutput() = 0;
    protected:
        QListIterator<QMap<QString,QVariant>> outputLinesIterator();
    private:
        QList<QMap<QString,QVariant>> outputLines;
    };

    class TextOutputWriter : public OutputWriter {
    public:
        QString getOutput() override;
    };

    class JsonOutputWriter : public OutputWriter {
    public:
        QString getOutput() override;
    };

    class CsvOutputWriter : public OutputWriter {
    public:
        QString getOutput() override;
    };

private:
    QString findFormat(QStringList arguments);
    QStringList allowedFormats;
    OutputWriter *getWriter(QString format);
    Settings settings;
};

#endif // LISTMODELSCOMMAND_H
