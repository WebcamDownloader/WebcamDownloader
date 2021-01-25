#ifdef __WIN32
#include "windows.h"
#endif
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QQmlEngine>
#include <QQmlContext>
#include <QSharedMemory>

#include "webcamregistry.h"
#include "webcaminfo.h"
#include "settings.h"
#include "newversionchecker.h"

#include "console/console.h"

int main(int argc, char *argv[])
{
    constexpr bool debugCli = false;

    if (argc > 1 || debugCli) {
        QCoreApplication app(argc, argv);
        Console console;
        if (debugCli) {
            return console.handler(app.arguments() << "help");
        }
        return console.handler(&app);
    } else {
#ifdef __WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
    }

    // todo: protect against crashes once Linux version is released
    QSharedMemory lock("71AD6F2B-13BF-425C-9455-B0569B79C600"); // same uuid as in installer
    if (!lock.create(512, QSharedMemory::ReadWrite)) {
        return -42;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qRegisterMetaType<WebcamInfo>("WebcamInfo");
    app.setOrganizationName("WebcamDownloader");
    app.setOrganizationDomain("WebcamDownloader");

    QTranslator translator;
    if (!translator.load("WebcamDownloader_" + QLocale::system().name(), ":/translations")) {
        translator.load("WebcamDownloader_en_US", ":/translations");
    }
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<WebcamRegistry>("webcam.downloader", 1, 0, "WebcamRegistry");
    qmlRegisterType<NewVersionChecker>("webcam.downloader", 1, 0, "NewVersionChecker");
    engine.rootContext()->setContextProperty("settings", new Settings(false, &app));
    engine.load(url);

    return app.exec();
}
