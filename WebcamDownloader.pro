QT += quick network quickcontrols2

CONFIG += c++17 console

RC_ICONS = icon.ico

include(singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QGuiApplication

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        chaturbatehost.cpp \
        console/addmodelcommand.cpp \
        console/command.cpp \
        console/console.cpp \
        console/downloadcommand.cpp \
        console/helpcommand.cpp \
        console/listhostscommand.cpp \
        console/listmodelscommand.cpp \
        console/removemodelcommand.cpp \
        console/settingscommand.cpp \
        ffmpeg.cpp \
        main.cpp \
        modelsetting.cpp \
        newversionchecker.cpp \
        settings.cpp \
        stripchathost.cpp \
        useragentgenerator.cpp \
        webcaminfo.cpp \
        webcamregistry.cpp \
        worker.cpp

RESOURCES += qml.qrc translations.qrc

TRANSLATIONS += \
    WebcamDownloader_en_US.ts \
    WebcamDownloader_cs_CZ.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    chaturbatehost.h \
    console/addmodelcommand.h \
    console/command.h \
    console/console.h \
    console/downloadcommand.h \
    console/helpcommand.h \
    console/listhostscommand.h \
    console/listmodelscommand.h \
    console/removemodelcommand.h \
    console/settingscommand.h \
    ffmpeg.h \
    modelsetting.h \
    newversionchecker.h \
    settings.h \
    stripchathost.h \
    useragentgenerator.h \
    webcamhost.h \
    webcaminfo.h \
    webcamregistry.h \
    worker.h
