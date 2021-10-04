import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3 as Dialogs

ApplicationWindow {
    width: settings.getWindowWidth()
    height: settings.getWindowHeight()
    visible: true
    title: qsTr('window-title-settings');
    onClosing: {
        optionsPage.active = false;
    }

    Column {
        spacing: 10
        padding: 10

        Row {
            spacing: parent.spacing
            Label {
                text: qsTr('option-close-to-tray')
                height: optionCloseToTray.height
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox {
                id: optionCloseToTray
                model: [{text: qsTr('yes'), value: true}, {text: qsTr('no'), value: false}]
                textRole: "text"
                valueRole: "value"
                currentIndex: {
                    const val = settings.closeToTray();
                    let index = 0;
                    for (const option of model) {
                        if (option.value === val) {
                            return index;
                        }

                        ++index;
                    }
                    return -1;
                }
                onActivated: {
                    settings.setCloseToTray(currentValue);
                }
            }
        }
        Row {
            spacing: parent.spacing
            Label {
                text: qsTr('option-check-for-new-versions')
                height: optionCloseToTray.height
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox {
                id: optionCheckForNewVersions
                model: [{text: qsTr('yes'), value: true}, {text: qsTr('no'), value: false}]
                textRole: "text"
                valueRole: "value"
                currentIndex: {
                    const val = settings.checkForNewVersions;
                    let index = 0;
                    for (const option of model) {
                        if (option.value === val) {
                            return index;
                        }

                        ++index;
                    }
                    return -1;
                }
                onActivated: {
                    settings.checkForNewVersions = currentValue;
                }
            }
        }
        Row {
            spacing: parent.spacing
            Label {
                text: qsTr('option-download-directory')
                height: optionCloseToTray.height
                verticalAlignment: Text.AlignVCenter
            }
            TextField {
                function setDownloadDirectory(dir) {
                    settings.downloadDirectory = dir;
                }

                id: optionDownloadDirectory
                enabled: false
                text: settings.downloadDirectory
            }
            Button {
                text: qsTr('button-browse-files')
                onClicked: {
                    chooseDownloadDirectoryDialog.open();
                }
            }
            Dialogs.FileDialog {
                id: chooseDownloadDirectoryDialog
                folder: "file:///" + optionDownloadDirectory.text
                selectFolder: true
                onAccepted: {
                    optionDownloadDirectory.setDownloadDirectory(fileUrl)
                }
            }
        }

        Row {
            spacing: parent.spacing
            Label {
                text: qsTr('option-language')
                height: optionCloseToTray.height
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox {
                id: optionLanguage
                model: [{text: qsTr('option-language-system'), value: ''}, {text: 'English', value: 'en_US'}, {text: 'Čeština', value: 'cs_CZ'}]
                textRole: "text"
                valueRole: "value"
                currentIndex: {
                    const val = settings.language;
                    let index = 0;
                    for (const option of model) {
                        if (option.value === val) {
                            return index;
                        }

                        ++index;
                    }
                    return -1;
                }
                onActivated: {
                    settings.language = currentValue;
                }
            }
        }
    }
}
