/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11
import flowmatic 1.0

Rectangle {
    id: flowNode

    width: 64
    height: 32
    radius: 6
    border.width: 1
    color: defaultColor
    border.color: "black"
    property alias name: data.name
    property alias id: data.id
    property alias inputId: data.inputId
    property string typeNickname: "+"
    property point inSocketPos: Qt.point(0, height / 2)
    property point outSocketPos: Qt.point(x + width, y + height / 2)
    property point inputPos: inSocketPos
    property point inputPosLocal: Qt.point(inputPos.x - x, inputPos.y - y)
    property color defaultColor: "green"
    property color hiliteColor: "light green"

    NodeData {
        id: data
        name: "node"
        value: 100
    }

    Text {
        text: name + " (" + typeNickname + ")"
        color: "#EEEEEE"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 10
    }

    Rectangle {
        width: 5
        height: 5
        radius: 3
        color: "black"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 4
        anchors.bottomMargin: 4
    }

    Shape {
        ShapePath {
            strokeColor: "red"
            strokeWidth: 3
            fillColor: "transparent"
            //capStyle: ShapePath.RoundCap

            startX: inputPosLocal.x
            startY: inputPosLocal.y
            PathLine {
                x: inSocketPos.x
                y: inSocketPos.y
            }
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        propagateComposedEvents: true
        acceptedButtons: Qt.AllButtons
        hoverEnabled: true

        drag.target: parent
        drag.axis: Drag.XAndYAxis

        onEntered: {
            flowNode.color = hiliteColor;
        }
        onExited: {
            if (!pressed) {
                flowNode.color = defaultColor;
            }
        }
        onPressed: {
            flowNode.color = hiliteColor;
        }
        onReleased: {
            flowNode.color = defaultColor;            
        }
        onPressAndHold: mouse.accepted = false
        onClicked: {
        }
    }
}

