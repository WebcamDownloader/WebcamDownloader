import Qt.labs.platform 1.1 as Labs
import Qt.labs.qmlmodels 1.0

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3 as Dialogs

import webcam.downloader 1.0

import "qrc:/pages" as Pages

ApplicationWindow {
    property var webcamConfig: ({})
    property var downloading: ({})
    id: window
    visible: true
    width: settings.getWindowWidth()
    height: settings.getWindowHeight()
    minimumWidth: 850
    minimumHeight: 480
    title: qsTr("app-title")

    menuBar: MenuBar {
        Menu {
            title: qsTr('menu-options')
            MenuItem {
                text: qsTr('menu-settings')
                onTriggered: optionsPage.active = true;
            }
        }
        Menu {
            title: qsTr("menu-help")
            MenuItem {
                text: qsTr("menu-how-to-use")
                onTriggered: helpPage.active = true
            }
        }
    }

    Labs.SystemTrayIcon {
        id: trayIcon
        icon.source: "qrc:/icon.png"
        visible: settings.closeToTray()

        menu: Labs.Menu {
            id: trayMenu
            Labs.MenuItem {
                text: qsTr('tray-quit')
                onTriggered: Qt.quit()
            }
        }

        onActivated: {
            if (reason !== Labs.SystemTrayIcon.Context) {
                window.show();
            }
        }
    }

    Loader {
        id: optionsPage
        active: false
        sourceComponent: Pages.Settings {}
    }

    Loader {
        id: helpPage
        active: false
        sourceComponent: Pages.Help {}
    }

    WebcamRegistry {
        id: registry
        onResults: {
            modelNotFound.opacity = 0;
            settings.setModelData(result.host, result.modelName)
            if (typeof webcamConfig[result.host] === 'undefined') {
                webcamConfig[result.host] = {};
            }
            webcamConfig[result.host][result.modelName] = result;
            if (
                result.isOnline
                && settings.getModelData(result.host, result.modelName).autoDownload
                && settings.autoDownloadsEnabled
            ) {
                registry.startDownload(result, settings.downloadDirectory);
            }
        }
        onFetchingInfoFailed: {
            modelNotFound.opacity = 1;
        }
        onDownloadStarted: {
            if (typeof downloading[host] === 'undefined') {
                downloading[host] = {};
            }
            downloading[host][modelName] = true;
        }
        onDownloadEnded: {
            if (typeof downloading[host] === 'undefined') {
                downloading[host] = {};
            }
            downloading[host][modelName] = undefined;
        }
    }

    NewVersionChecker {
        id: newVersionChecker
        onNewVersionFound: {
            newVersionFoundDialog.version = version;
            newVersionFoundDialog.open();
        }
    }

    Connections {
        target: settings
        function onModelsUpdated() {
            const modelData = settings.getModels();
            const models = [];
            for (const host in modelData) {
                if (!modelData.hasOwnProperty(host)) {
                    continue;
                }
                const hostModels = modelData[host];
                const friendlyName = registry.getFriendlyName(host);
                for (const model of hostModels) {
                    model.hostFriendlyName = friendlyName;
                    model.host = host;
                    models.push(model);
                }
            }
            table.model = models;
        }
    }

    Dialog {
        property string version: ''
        id: newVersionFoundDialog
        anchors.centerIn: parent
        title: qsTr("title-new-version-found")
        modal: true
        standardButtons: Dialog.Yes | Dialog.No
        onAccepted: {
            registry.openUrl("https://github.com/WebcamDownloader/WebcamDownloader/releases/latest");
        }

        Label {
            text: qsTr("text-new-version-found").arg(newVersionFoundDialog.version)
        }
    }

    Column {
        anchors.fill: parent
        padding: 10
        spacing: 10
        Row {
            width: parent.width
            spacing: 10
            ComboBox {
                id: selectHost
                textRole: "displayName"
                valueRole: "value"
                onActivated: {
                    registry.host = currentValue;
                }
                Component.onCompleted: {
                    activated(currentIndex);
                }
            }
            TextField {
                id: modelNameOrUrl
                placeholderText: qsTr("placeholder-model-name")
                width: parent.width - parent.spacing * 4 - selectHost.width - fetchInfoButton.width
            }
            Button {
                id: fetchInfoButton
                text: qsTr("fetch-info-button-text")
                onClicked: {
                    registry.fetchInfo(modelNameOrUrl.text);
                }
            }
        }

        Text {
            id: modelNotFound
            color: "red"
            opacity: 0
            text: qsTr("error-model-not-found")
        }

        Row {
            width: parent.width
            spacing: 10

            Column {
                width: parent.width * 0.8 - parent.spacing
                spacing: 20
                Text {
                    id: modelsLabel
                    text: qsTr("label-models")
                    font.pixelSize: 25
                    font.bold: true
                }


                Column {
                    property var model: []
                    property var widths: [0.25, 0.2, 0.1, 0.15, 0.2, 0.2]
                    property int padding: 5

                    function getWidth(index) {
                        return widths[index] * width - padding * 2;
                    }

                    id: table
                    width: parent.width
                    height: 100

                    Row {
                        Text {
                            width: table.getWidth(0)
                            padding: table.padding
                            text: qsTr('table-header-model-name')
                            font.bold: true
                        }
                        Text {
                            width: table.getWidth(1)
                            padding: table.padding
                            text: qsTr('table-header-friendly-hostname')
                            font.bold: true
                        }
                        Text {
                            width: table.getWidth(2)
                            padding: table.padding
                            text: qsTr('table-header-status')
                            font.bold: true
                        }
                        Text {
                            width: table.getWidth(3)
                            padding: table.padding
                            text: qsTr('table-header-download')
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        Text {
                            width: table.getWidth(4)
                            padding: table.padding
                            text: qsTr('table-header-auto-download')
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        Text {
                            width: table.getWidth(5)
                            padding: table.padding
                            text: qsTr('table-header-delete')
                            font.bold: true
                        }
                    }

                    Repeater {
                        model: parent.model

                        Row {
                            Text {
                                width: table.getWidth(0)
                                padding: table.padding
                                text: modelData.modelName
                            }
                            Text {
                                width: table.getWidth(1)
                                padding: table.padding
                                text: modelData.hostFriendlyName
                            }
                            Text {
                                id: status
                                width: table.getWidth(2)
                                padding: table.padding
                                text: qsTr('status-unknown')
                            }
                            CheckBox {
                                property bool isOnline: false
                                id: downloadCheckbox
                                enabled: !autoDownloadCheckbox.checked && isOnline
                                padding: table.padding
                                width: table.getWidth(3)
                                indicator.width: 15
                                indicator.height: indicator.width
                                indicator.implicitWidth: indicator.width
                                indicator.implicitHeight: indicator.height
                                onEnabledChanged: {
                                    if (!enabled) {
                                        checked = false;
                                        isOnline = false;
                                    }
                                }
                                onCheckedChanged: {
                                    startDownloadsButton.changed = startDownloadsButton.changed.filter(
                                        item => !(item.host === modelData.host && item.modelName === modelData.modelName)
                                    );
                                    startDownloadsButton.enabled = true;
                                    startDownloadsButton.changed.push({
                                        host: modelData.host,
                                        modelName: modelData.modelName,
                                        download: checked
                                    });
                                }
                            }
                            CheckBox {
                                id: autoDownloadCheckbox
                                padding: table.padding
                                width: table.getWidth(4)
                                checked: modelData.autoDownload
                                indicator.width: 15
                                indicator.height: indicator.width
                                indicator.implicitWidth: indicator.width
                                indicator.implicitHeight: indicator.height
                                onCheckedChanged: {
                                    settings.setModelData(modelData.host, modelData.modelName, checked);
                                }
                            }
                            Text {
                                padding: table.padding
                                width: table.getWidth(5)
                                text: qsTr('table-header-delete')
                                color: "red"
                                font.underline: true
                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        settings.deleteModel(modelData.host, modelData.modelName);
                                    }
                                }
                            }

                            Timer {
                                repeat: true
                                interval: 1000
                                running: true
                                onTriggered: {
                                    if (
                                      typeof downloading[modelData.host] !== 'undefined'
                                      && typeof downloading[modelData.host][modelData.modelName] !== 'undefined'
                                    ) {
                                        status.text = qsTr('status-downloading');
                                        downloadCheckbox.isOnline = true;
                                    } else if (
                                        typeof webcamConfig[modelData.host] !== 'undefined'
                                        && typeof webcamConfig[modelData.host][modelData.modelName] !== 'undefined'
                                    ) {
                                        if (window.webcamConfig[modelData.host][modelData.modelName].isOnline) {
                                            status.text = qsTr('status-online');
                                            downloadCheckbox.isOnline = true;
                                        } else {
                                            status.text = qsTr('status-offline');
                                            downloadCheckbox.isOnline = false;
                                        }
                                    } else {
                                        status.text = qsTr('status-unknown');
                                        downloadCheckbox.isOnline = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Column {
                width: parent.width * 0.2
                spacing: 10

                Text {
                    text: qsTr("label-actions")
                    font.pixelSize: modelsLabel.font.pixelSize
                    font.bold: modelsLabel.font.bold
                }

                Button {
                    property var changed: []

                    id: startDownloadsButton
                    text: qsTr("button-start-downloads")
                    width: openDownloadsDirButton.width
                    onClicked: {
                        enabled = false;
                        for (const key in changed) {
                            if (!changed.hasOwnProperty(key)) {
                                continue;
                            }

                            const item = changed[key];
                            if (item.download) {
                                registry.startDownload(webcamConfig[item.host][item.modelName], settings.downloadDirectory);
                            } else {
                                registry.stopDownload(item.host, item.modelName);
                            }
                        }
                        changed = [];
                    }
                }

                Button {
                    text: qsTr("button-stop-all-downloads");
                    width: openDownloadsDirButton.width
                    onClicked: {
                        startDownloadsButton.enabled = true;
                        const changed = [];
                        for (const host in downloading) {
                            if (!downloading.hasOwnProperty(host)) {
                                continue;
                            }
                            const models = Object.keys(downloading[host]);
                            for (const modelName of models) {
                                changed.push({host, modelName, download: true});
                            }
                        }
                        startDownloadsButton.changed = changed;
                        registry.stopAllDownloads();
                        settings.autoDownloadsEnabled = false;
                    }
                }

                Button {
                    width: openDownloadsDirButton.width
                    text: settings.autoDownloadsEnabled
                          ? qsTr('button-disable-autodownloads')
                          : qsTr('button-enable-autodownloads')
                    onClicked: {
                        settings.autoDownloadsEnabled = !settings.autoDownloadsEnabled;
                    }
                }

                Button {
                    id: openDownloadsDirButton
                    text: qsTr('button-open-downloads')
                    onClicked: {
                        registry.openDirectory(settings.downloadDirectory);
                    }
                }
            }
        }
    }

    onWidthChanged: {
        settings.setWindowWidth(width);
    }

    onHeightChanged: {
        settings.setWindowHeight(height);
    }

    function updateStatuses(autodownload) {
        const modelData = settings.getModels();
        for (const host in modelData) {
            if (!modelData.hasOwnProperty(host)) {
                continue;
            }
            for (const model of modelData[host]) {
                if (
                    (autodownload === true && model.autoDownload)
                    || (autodownload === false && !model.autoDownload)
                    || (autodownload === null || autodownload === undefined)
                ) {
                    registry.fetchInfo(host, model.modelName);
                }
            }
        }
    }

    Timer {
        id: nonAutoDownloadTimer
        repeat: true
        running: true
        interval: 2 * 60 * 1000 // two minutes
        onTriggered: {
            updateStatuses(false);
        }
    }

    Timer {
        id: autoDownloadTimer
        repeat: true
        running: settings.autoDownloadsEnabled
        interval: 10 * 1000 // 10 seconds
        onTriggered: {
            updateStatuses(true);
        }
    }

    onClosing: {
        if (settings.closeToTray()) {
            trayIcon.show();
            window.hide();
        }
    }

    Component.onCompleted: {
        const model = [];
        for (const value in registry.types) {
            if (!registry.types.hasOwnProperty(value)) {
                continue;
            }
            const displayName = registry.types[value];
            model.push({displayName, value});
        }
        selectHost.model = model;
        settings.modelsUpdated();
        updateStatuses();
        if (settings.checkForNewVersions) {
            newVersionChecker.checkForNewVersion();
        }
    }
}
