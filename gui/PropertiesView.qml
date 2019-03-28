/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

Rectangle {
    id: propertiesView
    border.width: 1
    border.color: "#85a3e0"
    color: "#222222"

    ScrollView {
        anchors.fill: parent
        anchors.margins: 1
        clip: true
        //ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        contentWidth: parent.width
        contentHeight: 1000
    }
}
