import QtQuick 2.0
import QtCharts 2.0

Item {
    width: 600
    height: 400
    anchors.fill: parent
    property var topWords

    function readTop() {
            for (var prop in topWords) {
                mySeries.append(prop, topWords[prop]);
                //console.log("Object item:", prop, "=", topMap[prop])
            }
        }

    //![1]
    ChartView {
        title: "Word Top"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true


        BarSeries {
            id: mySeries
        }
    }

    Component.onCompleted: {
        /*for(var i = 0; i<topWords.size; i++) {
            mySeries.append("newWord", 0);
        }*/
    }

    //![1]
}
