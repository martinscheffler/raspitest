import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.VirtualKeyboard 2.0
Item {
TextEdit{
    text: "Edit!!!"

    }

    InputPanel {
        id: inputPanel
        z: 89
        y: active ? parent.height - height : parent.height
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
