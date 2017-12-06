import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2

Item {
    id: item1
    property alias chartView: chartView
    property alias btn_update: btn_update

    Connections {
        target: netManager
        onValueUpdated: {

            series.append(x, y)
            if (x > xAxis.max) {
                xAxis.max = x
            }
            if (y > yAxis.max) {
                yAxis.max = y
            }
            if (btn_update.checked) {
                xAxis.min = txt_mintime.text
                xAxis.max = txt_maxtime.text
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
                text: qsTr("Daily Stock_FB - Open")
                Layout.fillWidth: false
                z: 1
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
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        ChartView {
            id: chartView
            plotAreaColor: "#aed4de"
            localizeNumbers: false
            anchors.rightMargin: 0
            anchors.bottomMargin: -41
            anchors.leftMargin: 0
            anchors.topMargin: 0
            backgroundColor: "#28f6c9"
            titleColor: "#bd0707"
            title: "Daily chart"
            anchors.fill: parent
            theme: ChartView.ChartThemeLight

            ValueAxis {
                id: yAxis
                color: "#ffffff"
                gridLineColor: qsTr("#e81ce8")
                titleText: "OpenValue"
                titleVisible: true
                gridVisible: true
                tickCount: 11
                min: 150
                max: 200
            }
            DateTimeAxis {
                id: xAxis
                color: "#ffffff"
                gridLineColor: "#e81ce8"
                tickCount: 20
                visible: true
                labelsAngle: 90
                gridVisible: true
                format: "yyyy-MM-dd"
                min: "2017-08-01"
                max: "2017-12-01"
            }

            GridView{

            }
            Grid{

            }
            LineSeries {
                id: series
                axisX: xAxis
                axisY: yAxis
                name: "Daily Stock_FB series"
                width: 2
                color: qsTr("#e91e1e")
                pointLabelsColor: qsTr("#e91e1e")
                visible: true

            }

            Button {
                id: btn_update
                x: 440
                y: 24
                width: 93
                height: 30
                text: qsTr("Update")
                highlighted: true
                font.pointSize: 12
                font.bold: true
                spacing: 0
                focusPolicy: Qt.NoFocus
                onClicked: xAxis.min = txt_mintime.text
                onPressed: xAxis.max = txt_maxtime.text
            }

            TextField {
                id: txt_mintime
                x: 20
                y: 24
                width: 154
                height: 30
                text: qsTr("2017-08-01")
            }

            TextField {
                id: txt_maxtime
                x: 237
                y: 24
                width: 167
                height: 30
                text: qsTr("2017-12-01")
            }
        }
    }
}
