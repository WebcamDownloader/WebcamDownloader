#ifdef __WIN32
#include "windows.h"
#endif
#ifndef NO_GUI
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#endif
#include <QTranslator>
#include <QSharedMemory>
#include <QTimer>
#include <QTextStream>

#include <SingleApplication>

#include "webcamregistry.h"
#include "webcaminfo.h"
#include "settings.h"
#include "newversionchecker.h"

#include "console/console.h"

int main(int argc, char *argv[])
{
    constexpr bool debugCli = false;
#ifndef NO_GUI
    constexpr bool forceCli = false;
#else
    constexpr bool forceCli = true;
#endif

    if (argc > 1 || debugCli || forceCli) {
        QCoreApplication app(argc, argv);
        qRegisterMetaType<WebcamInfo>("WebcamInfo");
        Console console;

        Command *command;
        auto arguments = app.arguments();
        if (forceCli && arguments.size() == 1) {
            arguments << "help";
        }
        if (debugCli) {
            command = console.findCommand(arguments << "download");
        } else {
            command = console.findCommand(arguments);
        }
        arguments.removeAt(0);
        command->setArguments(arguments);

        QObject::connect(command, &Command::commandFinished, &app, [](int exitCode) {
            QCoreApplication::exit(exitCode);
        });
        QTimer::singleShot(0, command, &Command::run);

        return app.exec();
    } else {
#ifdef __WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
    }
#ifndef NO_GUI

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    SingleApplication app(argc, argv);
    qRegisterMetaType<WebcamInfo>("WebcamInfo");
    app.setOrganizationName("WebcamDownloader");
    app.setOrganizationDomain("WebcamDownloader");

    auto settings = new Settings(false, &app);

    QString language = settings->language();
    if (language.isEmpty()) {
        language = QLocale::system().name();
    }

    QTranslator translator;
    if (!translator.load("WebcamDownloader_" + language, ":/translations")) {
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
    engine.rootContext()->setContextProperty("settings", settings);
    engine.load(url);

    return app.exec();
#endif
}
