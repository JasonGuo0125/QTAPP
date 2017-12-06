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

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Stock_FB - Open")
        }
        TabButton {
            text: qsTr("Stock_FB - High")
        }
        TabButton {
            text: qsTr("Stock_FB - Close")
        }
    }
}
