import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Window 2.12

ApplicationWindow {
    id: root
    width: settings.getWindowWidth()
    height: settings.getWindowHeight()
    visible: true
    title: qsTr('window-title-help');
    onClosing: {
        helpPage.active = false;
    }

    ScrollView {
        width: parent.width
        height: parent.height
        clip: true
        ScrollBar.vertical.policy: ScrollBar.AsNeeded

        Label {
            text: qsTr("text-how-to-use")
            padding: 20
            width: root.width
            wrapMode: Label.WordWrap
        }
    }
}
