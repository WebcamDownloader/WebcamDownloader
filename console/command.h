#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    virtual QString name() = 0;
    virtual QString description() = 0;
    virtual QString help() = 0;
    virtual bool isDefault();
    virtual void setArguments(QStringList &arguments);
    virtual bool isInternal();

protected:
    QStringList *arguments = nullptr;

signals:
    void commandFinished(int exitCode = 0);

public slots:
    virtual void run() = 0;
};

#endif // COMMAND_H
