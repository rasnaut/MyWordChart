import QtQuick 2.0
import QtCharts 2.0

Item {
    width: 700
    height: 480
    anchors.fill: parent

    function readTop(topWords) {
            console.log("read top")
            for (var prop in topWords) {
                mySeries.append(prop, [topWords[prop]]);
                console.log("Object item:", prop, "=", topWords[prop])
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
            axisY: ValueAxis {
                id: valueAxis
                min: 0
                max: 50
            }

            //BarSet { label: "Test"; values: [2] }
        }
    }

    Component.onCompleted: {
        /*for(var i = 0; i<topWords.size; i++) {
            mySeries.append("newWord", 0);
        }*/
    }

    //![1]
}
