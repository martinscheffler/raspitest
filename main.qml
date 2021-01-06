import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.4
import QtCharts 2.15

ApplicationWindow {
    id: window
    objectName: "mainWindow"
    width: 800
    height: 480
    visible: true
    title: qsTr("Raspi Demo")
    property real temperatureSensor

    TabView {
        anchors.fill: parent
        id: tabs

        Component.onCompleted: {

            var tab1 = tabs.addTab("Temperature", Qt.createComponent("temperature.qml"));
            tab1.active = true;

            var tab2 = tabs.addTab("Text Edit", Qt.createComponent("text.qml"));
            tab2.active = true;

            var tab3 = tabs.addTab("List", Qt.createComponent("MyList.qml"));
            tab3.active = true;
        }
    }
}
