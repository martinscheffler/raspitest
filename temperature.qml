import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtCharts 2.14

Rectangle {
    id: rect

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered:
        {
            var date = new Date();

            lineSeries.append( date, temperatureSensor )
            while(lineSeries.count > 60) {
                lineSeries.remove(0);
                console.log("Removed!");
            }

            axisX.max = date;
            axisX.min = new Date(date.getTime() - 60000);
        }
    }

    Text {
        id: helloText
        objectName: "textField"
        text: "Temperature: " + window.temperatureSensor + "°";
        y: 30
        anchors.horizontalCenter: rect.horizontalCenter
        font.pointSize: 24; font.bold: true
    }

    ChartView {
        title: "CPU Temperature"
        id: chart
        legend.visible: false

        DateTimeAxis {
            id: axisX
            tickCount: 7
            format: "HH:mm:ss"
        }

        ValueAxis {
            id: axisY
            min: -10
            max: 60

        }

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: helloText.bottom
        anchors.bottom: parent.bottom
        antialiasing: true


        LineSeries {
            name: "LineSeries"
            id: lineSeries
            axisX: axisX
            axisY: axisY
        }
    }

}
