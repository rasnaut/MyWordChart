import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {
    id: root
    visible: true
    width: 700
    height: 480

    signal fileUrlSignal(msg: string)

    property bool isTopReady: false

    FileDialog {
        id: fileDialog
        //visible: true
        modality: Qt.WindowModal
        title: "Choose a text file"
        //selectExisting: fileDialogSelectExisting.checked
        selectMultiple: false
        //selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Text files (*.txt)", "All files (*)" ]
        selectedNameFilter: "Text files (*.txt)"
        onAccepted: {
            root.fileUrlSignal(fileUrls);
            openButton.visible = false;
        }
        onRejected: { console.log("Rejected") }
    }

    Button {
        id: openButton
        text: "Open"
        visible: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: fileDialog.open()
    }

    ProgressBar {
        id: prg
        visible: !isTopReady
        minimumValue: 0   // C++ loop starts out with 0
        maximumValue: 100 // C++ loop ends with "Count"

    }

    ChartsView {
        id: chart
        visible: isTopReady
    }

    Connections {
        target: fileReader
        function onProgressChanged(progress) {
            prg.value = progress;
        }
        function onTopWordsReadyChanged(isReady) {
            console.log("QML: onTopWordsReadyChanged!!!!")
            isTopReady = isReady;
            if(isReady) {
                chart.readTop(fileReader.topWords);
            }
        }
    }
}
