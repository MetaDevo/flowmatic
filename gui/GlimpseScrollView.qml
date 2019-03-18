/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11
import flowmatic 1.0

Rectangle {
    id: glimpseScrollView
    width: 800
    height: 200
    border.width: 1
    border.color: "#85a3e0"
    color: "#222222"    

    ScrollView {
        anchors.fill: parent
        anchors.margins: 1
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        //ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        contentWidth: 1920
        contentHeight: parent.height

        Rectangle {
            border.color: "#777777"
            border.width: 1
            width: 182
            height: 182
            x: 2
            y: 2

            GlimpseImage {
                schematicId: 0
                nodeId: 0
                x: 1
                y: 1
            }
        }

        Rectangle {
            border.color: "#777777"
            border.width: 1
            width: 182
            height: 182
            x: 186
            y: 2

            GlimpseImage {
                schematicId: 0
                nodeId: 1
                x: 1
                y: 1
            }
        }
    }
}
