import QtQuick 2.0
import QtCharts 2.0

Item {
    width: 700
    height: 480
    anchors.fill: parent

    function readTop(topWords) {
            mySeries.clear();
            var max = 0;
            for (var prop in topWords) {
                mySeries.append(prop, [topWords[prop]]);
                if(max < topWords[prop]) max = topWords[prop];
            }
            mySeries.maximum = max;
        }

    ChartView {
        title: "Word Top"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        BarSeries {
            id: mySeries
            property var maximum: 10

            axisY: ValueAxis {
                id: valueAxis
                min: 0
                max: mySeries.maximum
                tickCount: 5
            }

            BarSet { values: [1] }
        }
    }
}
