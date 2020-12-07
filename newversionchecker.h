#ifndef NEWVERSIONCHECKER_H
#define NEWVERSIONCHECKER_H

#include <QObject>
#include <QVersionNumber>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class NewVersionChecker : public QObject
{
    Q_OBJECT
public:
    explicit NewVersionChecker(QObject *parent = nullptr);

signals:
    void newVersionFound(QString version);

public slots:
    void checkForNewVersion();

private slots:
    void onLatestVersionReceived(QNetworkReply *reply);

private:
    QVersionNumber currentVersion();
    QNetworkAccessManager manager;
};

#endif // NEWVERSIONCHECKER_H
