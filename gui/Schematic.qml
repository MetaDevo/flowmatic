/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

Rectangle {
    id: schematic
    width: 800
    height: 600
    border.width: 1
    border.color: "#85a3e0"

    property int gridSize: 32

    ScrollView {
        anchors.fill: parent
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

        // test
        FlowNode {
            id: node1
            x: gridSize * 2 - width / 2
            y: gridSize * 3 - height / 2
        }
        FlowNode {
            id: node2
            inputId: node1.id
            inputPos: node1.outSocketPos
            x: gridSize * 6 - width / 2
            y: gridSize * 3 - height / 2
        }
        FlowNode {
            id: resultNode
            name: "result"
            inputId: node2.id
            inputPos: node2.outSocketPos
            x: gridSize * 9 - width / 2
            y: gridSize * 5 - height / 2
        }
    }
}