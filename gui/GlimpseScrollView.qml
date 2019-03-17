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
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        contentWidth: 1920
        contentHeight: parent.height

        Rectangle {
            color: "#333333"
            width: 180
            height: 180

            GlimpseImage {

            }
        }
        Rectangle {
            color: "#333333"
            width: 180
            height: 180
            x: 200
        }
    }
}
