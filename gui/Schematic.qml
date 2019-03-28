/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

Rectangle {
    id: schematic
    width: 800
    height: 400
    border.width: 1
    border.color: "#85a3e0"

    property int gridSize: 32
    property int navHeight: 34
    property int seqPos: 0

    ScrollView {
        id: scrollContent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height - navHeight
        anchors.margins: 1
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        contentWidth: bg.width
        contentHeight: bg.height

        Rectangle {
            id: bg
            color: "#222222"
            width: 1920
            height: 1080

            Repeater  {
                model: bg.height / gridSize
                delegate: Rectangle {
                    x: 0
                    y: index * gridSize
                    width: parent.width
                    height: 1
                    color: "#333333"
                }
            }
            Repeater  {
                model: bg.width / gridSize
                delegate: Rectangle {
                    x: index * gridSize
                    y: 0
                    width: 1
                    height: parent.height
                    color: "#333333"
                }
            }
        }

        ////////////////////////////////////////////////////
        // Example nodes. Remove/change in your application.
        FlowNode {
            id: node1
            x: gridSize * 2 - width / 2
            y: gridSize * 3 - height / 2            
            name: "images"
            typeNickname: "imgseq"
            behavior: "imgseq"
            seqEnd: 2
        }
        FlowNode {
            id: node2
            inputId: node1.nodeId
            inputPos: node1.outSocketPos
            typeNickname: "imgflip"
            behavior: "imgflip"
            seqEnd: 2
            x: gridSize * 6 - width / 2
            y: gridSize * 3 - height / 2
        }
        FlowNode {
            id: resultNode
            name: "result"
            inputId: node2.nodeId
            inputPos: node2.outSocketPos
            x: gridSize * 9 - width / 2
            y: gridSize * 5 - height / 2
        }
        ///////////////////////////////////////////////////
    }

    Rectangle {
        id: navArea
        anchors.left: parent.left
        anchors.top: scrollContent.bottom
        width: parent.width
        height: navHeight
        border.width: 1
        border.color: "#85a3e0"
        color: "#222222"

        Button {
            id: scrubLeftButton
            icon.source: "qrc:/third-party/material-icons/ic_chevron_left_white_18dp.png"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 2
            height: 30

            onClicked: {
                if (node1.scrub(seqPos - 1)) {
                    seqPos--;
                }
                node1.preview();
            }
        }

        Button {
            id: scrubRightButton
            icon.source: "qrc:/third-party/material-icons/ic_chevron_right_white_18dp.png"
            anchors.left: scrubLeftButton.right
            anchors.top: parent.top
            anchors.margins: 2
            height: 30

            onClicked: {
                if (node1.scrub(seqPos + 1)) {
                    seqPos++;
                }
                node1.preview();
            }
        }

        Text {
            id: horSeqLabel
            text: "Frame: " + seqPos
            color: "#AAAAAA"
            anchors.left: scrubRightButton.right
            anchors.top: parent.top
            anchors.margins: 2
            font.pointSize: 10
        }

        Button {
            id: runButton
            text: "Run"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 2
            height: 30

            onClicked: {
                node1.run();
                //node1.update();
            }
        }
    }

}
