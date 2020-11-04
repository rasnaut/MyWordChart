import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {
    visible: true
    width: 580
    height: 480

    signal fileUrlSignal(msg: string)

    FileDialog {
        id: fileDialog
        visible: fileDialogVisible.checked
        modality: Qt.WindowModal
        title: "Choose a text file"
        //selectExisting: fileDialogSelectExisting.checked
        selectMultiple: false
        //selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Text files (*.txt)", "All files (*)" ]
        selectedNameFilter: "Text files (*.txt)"
        onAccepted: {
            root.qmlSignal(fileUrls);
        }
        onRejected: { console.log("Rejected") }
    }

    Button {
        text: "Open"
        visible: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: fileDialog.open()
    }

    ProgressBar {
        visible: false
        indeterminate: true
    }
}
