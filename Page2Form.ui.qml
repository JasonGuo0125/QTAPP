import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2

Item {
    id: item1
    property alias chartView: chartView
    Connections {
        target: netManager
        onValueUpdated2: {
            series2.append(x, y)
            if (x > xAxis.max) {
                xAxis.max = x
            }
            if (y > yAxis.max) {
                yAxis.max = y
            }
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            Text {
                id: text1
                color: "#e91e1e"
                text: qsTr("Daily Stock_FB - High")
                font.italic: true
                font.pointSize: 20
            }
        }
    }
    Item {
        id: item2
        x: 0
        y: 58
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        ChartView {
            id: chartView
            title: "Daily chart"
            anchors.fill: parent

            ValueAxis {
                id: yAxis
                titleText: "HighValue"
                titleVisible: true
                gridVisible: true
                tickCount: 11
                min: 150
                max: 200
            }
            DateTimeAxis {
                id: xAxis
                tickCount: 20
                visible: true
                labelsAngle: 90
                gridVisible: true
                format: "yyyy-MM-dd"
                min: "2017-08-01"
                max: "2017-12-01"
            }
            LineSeries {
                id: series2
                name: "Daily Stock_FB series"
                visible: true
                axisX: xAxis
                axisY: yAxis
            }
        }
    }
}
