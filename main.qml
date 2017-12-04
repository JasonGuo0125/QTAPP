import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("AlphaVantage TimeSeries")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {

        }

        Page2 {

        }
        Page3 {

        }

    }
//    RowLayout {
//        anchors.bottom: tabBar.top
//        anchors.bottomMargin: 10
//        anchors.horizontalCenter: parent.horizontalCenter
//        Button {
//            id: button1
//            text: qsTr("Refresh")
//            onClicked: {

//            }
//        }
//        Button {
//            id: button2
//            text: qsTr("Save")
//            onClicked: {

//            }
//        }
//    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("BitCoin - HUF")
        }
        TabButton {
            text: qsTr("BitCoin Volume")
        }
        TabButton {
            text: qsTr("BitCoin - USD")
        }
    }
}
