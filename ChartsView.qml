import QtQuick 2.0
import QtCharts 2.0

Item {
    width: 600
    height: 400
    //anchors.fill: parent

    //![1]
    ChartView {
        title: "Word Top"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        BarSeries {
            id: mySeries
            BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
            BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
            BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
        }
    }
    //![1]
}
