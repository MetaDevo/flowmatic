/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11
import flowmatic 1.0

Rectangle {
    id: flowNode

    width: nameLabel.width + 12
    height: 48
    radius: 6
    border.width: 1
    color: data.isSelected ? hiliteColor : defaultColor
    border.color: "black"
    property alias name: data.name
    property alias nodeId: data.uniqueId
    property alias inputId: data.inputId
    property alias typeNickname: data.typeNickname
    property alias seqStart: data.seqStart
    property alias seqEnd: data.seqEnd
    property point inSocketPos: Qt.point(0, height / 2)
    property point outSocketPos: Qt.point(x + width, y + height / 2)
    property point inputPos: inSocketPos
    property point inputPosLocal: Qt.point(inputPos.x - x, inputPos.y - y)
    property color defaultColor: "#D6A95D"
    property color hiliteColor: "#56AF4D"
    property color hoverColor: "#C97E00"
    property bool checkable: false

    function run() {
        data.run();
    }

    function preview() {
        data.preview();
    }

    function previewAll() {
        data.previewAll();
    }

    // interface to a C++ object
    NodeData {
        id: data
        name: "node"
        defaultValue: 100
    }

    Text {
        id: nameLabel
        text: name + " (" + typeNickname + ")"
        color: "#000000"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 4
        font.pointSize: 8
    }

    Text {
        id: seqLabel
        text: "[" + data.seqPos + "]"
        color: "#222222"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: nameLabel.bottom
        anchors.margins: 2
        font.pointSize: 8
    }

    Rectangle {
        id: runIndicator
        width: 8
        height: 8
        radius: 6
        color: data.isRunning ? "#10A400" : "black"
        border.width: 1
        border.color: data.isRunning ? "#71624A" : "#181613"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 4
        anchors.bottomMargin: 4
    }

    // connector line to an input
    ///@todo hook up multiple lines for nodes with multiple inputs
    Shape {
        ShapePath {
            strokeColor: "#6D447F"
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

    Image {
        source: "qrc:/third-party/material-icons/ic_check_black_12dp.png"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 4
        anchors.bottomMargin: 4
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
            //flowNode.color = hoverColor;
        }
        onExited: {
//            if (!pressed && !data.isSelected) {
//                flowNode.color = defaultColor;
//            }
        }
        onPressed: {
            //flowNode.color = hiliteColor;
        }
        onReleased: {
            //flowNode.color = defaultColor;
        }
        onPressAndHold: mouse.accepted = false
        onClicked: {
            data.select(selectedNode);
            selectedNode = data.uniqueId;
        }
    }
}

