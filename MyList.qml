import QtQuick 2.4
Rectangle {

ListView {
    id: listView
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.bottom: parent.bottom
    focus: true

    Component {
        id: highlightBar
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 120
            color: "#bb7f43"

            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
     }

    // Set the highlight delegate. Note we must also set highlightFollowsCurrentItem
    // to false so the highlight delegate can control how the highlight is moved.
    highlight: highlightBar
    highlightFollowsCurrentItem: false

    delegate: Item {
        id: myDelegate
        x: 5
        width: 160
        height: 120

        Row {
            id: row1
            spacing: 10


            Image{
                width: 100
                height: 100
                anchors.topMargin: 10
                anchors.top: parent.top

                source: imageSource
            }

            Text {
                text: name
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
            }
        }
        states: State {
            name: "Current"
            when: myDelegate.ListView.isCurrentItem
            PropertyChanges { target: myDelegate; x: 20 }
        }
        transitions: Transition {
            NumberAnimation { properties: "x"; duration: 200 }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: myDelegate.ListView.view.currentIndex = index
        }
    }
    model: ListModel {

        ListElement {
            name: "Cup of Coffee"
            imageSource: "resources/c1.png"
        }

        ListElement {
            name: "Mug of Coffee"
            imageSource: "resources/c2.png"
        }

        ListElement {
            name: "Frappucchino"
            imageSource: "resources/c3.png"
        }

        ListElement {
            name: "Tall Latte"
            imageSource: "resources/c4.png"
        }

        ListElement {
            name: "Beans"
            imageSource: "resources/c5.png"
        }

        ListElement {
            name: "Beans in paper bag"
            imageSource: "resources/c6.png"
        }

        ListElement {
            name: "Cup"
            imageSource: "resources/c7.png"
        }

        ListElement {
            name: "Pot"
            imageSource: "resources/c8.png"
        }
        ListElement {
            name: "Grinder"
            imageSource: "resources/c9.png"
        }
        ListElement {
            name: "Percolator"
            imageSource: "resources/c10.png"
        }
        ListElement {
            name: "Presser"
            imageSource: "resources/c11.png"
        }
        ListElement {
            name: "Filter"
            imageSource: "resources/c12.png"
        }
    }
}
}
