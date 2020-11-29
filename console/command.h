#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    virtual QString name() = 0;
    virtual int run(QStringList arguments) = 0;
    virtual QString description() = 0;
    virtual QString help() = 0;
    virtual bool isDefault();

signals:

};

#endif // COMMAND_H
